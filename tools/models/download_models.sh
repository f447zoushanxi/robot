#!/usr/bin/env bash
# Enhanced download script supporting:
#  - direct HTTP(S) URLs
#  - Hugging Face repo identifiers using hf:owner/repo[:subpath]
#
# Usage:
#   tools/models/download_models.sh
# It reads models_list.txt with lines: name|filename|url
# If a URL starts with hf:, this script will attempt to use the huggingface_hub Python
# package to download the repository files. Otherwise it will use curl/wget to fetch the URL.

set -euo pipefail
REPO_ROOT=$(git rev-parse --show-toplevel)
MODELS_DIR="$REPO_ROOT/ros_ws/src/robot_perception/models"
mkdir -p "$MODELS_DIR"

LIST_FILE="$MODELS_DIR/models_list.txt"
if [ ! -f "$LIST_FILE" ]; then
  echo "No models_list.txt found at $LIST_FILE"
  echo "Create the file with lines of the form: name|filename|url"
  exit 1
fi

# helper: download via huggingface_hub
hf_download() {
  repo_spec="$1"  # format: owner/repo or owner/repo:subpath
  outpath="$2"

  # ensure python deps
  if ! python3 -c "import huggingface_hub" >/dev/null 2>&1; then
    echo "python package 'huggingface_hub' not found, installing temporarily..."
    python3 -m pip install --user huggingface-hub
  fi

  python3 - <<PY
from huggingface_hub import hf_hub_download
import sys
spec = sys.argv[1]
out = sys.argv[2]
if ':' in spec:
    repo, sub = spec.split(':',1)
    # try to download the file/subpath
    try:
        path = sub
        local_path = hf_hub_download(repo_id=repo, filename=path)
        print(local_path)
    except Exception as e:
        raise
else:
    repo = spec
    # try to find an onnx file in the repo root by listing common filenames
    candidates = [
        'deepseek.onnx',
        'model.onnx',
        'onnx_model.onnx',
        'yolov8n.onnx',
        'yolov8.onnx'
    ]
    for c in candidates:
        try:
            local_path = hf_hub_download(repo_id=repo, filename=c)
            print(local_path)
            break
        except Exception:
            continue
    else:
        # fallback: download the entire repo snapshot and try to find first .onnx
        from huggingface_hub import snapshot_download
        sd = snapshot_download(repo_id=repo)
        import os
        for root,_,files in os.walk(sd):
            for f in files:
                if f.endswith('.onnx'):
                    print(os.path.join(root,f))
                    raise SystemExit(0)
        raise SystemExit(2)
PY
}

while IFS='|' read -r name filename url; do
  if [ -z "$name" ] || [ -z "$filename" ] || [ -z "$url" ]; then
    echo "Skipping invalid line: $name|$filename|$url"
    continue
  fi
  outpath="$MODELS_DIR/$filename"
  if [ -f "$outpath" ]; then
    echo "Model $filename already exists, skipping"
    continue
  fi
  echo "Processing $name -> $outpath"
  if [[ "$url" == hf:* ]]; then
    repo_spec="${url#hf:}"
    echo "Downloading from Hugging Face repo: $repo_spec"
    # attempt hf download; the python snippet will print a local path to the file
    tmp_local=$(hf_download "$repo_spec" "$outpath" 2>/dev/null || true)
    if [ -n "$tmp_local" ] && [ -f "$tmp_local" ]; then
      echo "Copying $tmp_local to $outpath"
      cp "$tmp_local" "$outpath"
    else
      echo "Failed to download ONNX file directly from HF repo $repo_spec."
      echo "You may need to provide an explicit subpath in models_list.txt like hf:owner/repo:sub/path/model.onnx"
      continue
    fi
  else
    # direct HTTP(S) download
    if command -v curl >/dev/null 2>&1; then
      echo "Downloading $url via curl"
      curl -L --fail -o "$outpath" "$url"
    elif command -v wget >/dev/null 2>&1; then
      echo "Downloading $url via wget"
      wget -O "$outpath" "$url"
    else
      echo "Neither curl nor wget available. Install one to download models."
      exit 2
    fi
  fi
  echo "Downloaded $outpath"
done < "$LIST_FILE"

echo "All listed models processed."
