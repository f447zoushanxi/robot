#!/usr/bin/env bash
# tools/train/quantize.sh
# Dynamic quantization using onnxruntime quantization
set -euo pipefail
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <model.onnx>"
  exit 1
fi
MODEL=$1
OUT=${2:-$(basename "$MODEL" .onnx).quant.onnx}
python - <<PY
from onnxruntime.quantization import quantize_dynamic, QuantType
quantize_dynamic('$MODEL', '$OUT', weight_type=QuantType.QInt8)
print('Quantized saved to', '$OUT')
PY
