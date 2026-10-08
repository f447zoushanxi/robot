#!/usr/bin/env bash
# tools/train/export_onnx.sh
# Export a trained YOLOv8 .pt to ONNX and copy to models dir
set -euo pipefail
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <weights.pt> [outname.onnx]"
  exit 1
fi
WEIGHTS=$1
OUTNAME=${2:-$(basename "$WEIGHTS" .pt).onnx}

python - <<PY
from ultralytics import YOLO
model = YOLO('$WEIGHTS')
model.export(format='onnx')
PY

# move result if exists
if [ -f "$(pwd)/$(basename $WEIGHTS .pt).onnx" ]; then
  mkdir -p ros_ws/src/robot_perception/models
  mv "$(basename $WEIGHTS .pt).onnx" ros_ws/src/robot_perception/models/$OUTNAME
  echo "Exported ONNX -> ros_ws/src/robot_perception/models/$OUTNAME"
else
  echo "ONNX export not found in cwd. Check export logs."
fi
