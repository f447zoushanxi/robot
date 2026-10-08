#!/usr/bin/env bash
# tools/train/train_yolov8.sh
# Simple wrapper to train YOLOv8n using Ultralytics CLI
set -euo pipefail
if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <data.yaml> [epochs] [imgsz]"
  exit 1
fi
DATA_YAML=$1
EPOCHS=${2:-50}
IMGSZ=${3:-640}
MODEL=${4:-yolov8n.pt}

echo "Training YOLOv8n with data=$DATA_YAML epochs=$EPOCHS imgsz=$IMGSZ model=$MODEL"
python -m ultralytics.yolo.train data="$DATA_YAML" model="$MODEL" epochs="$EPOCHS" imgsz="$IMGSZ"
