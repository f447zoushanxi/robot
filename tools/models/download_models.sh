#!/usr/bin/env bash
# Download models listed in models/models_list.txt
# Each line: <name>|<relative_filename>|<url>
# Example:
# deepseek_free|deepseek.onnx|https://example.com/path/to/deepseek.onnx
# alibaba_free|alibaba.onnx|https://example.com/path/to/alibaba.onnx
# us_free|us.onnx|https://example.com/path/to/us.onnx

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
  echo "Downloading $name -> $outpath"
  if command -v curl >/dev/null 2>&1; then
    curl -L --fail -o "$outpath" "$url"
  elif command -v wget >/dev/null 2>&1; then
    wget -O "$outpath" "$url"
  else
    echo "Neither curl nor wget available. Install one to download models."
    exit 2
  fi
  echo "Downloaded $outpath"
done < "$LIST_FILE"

echo "All listed models processed."
