# DEPLOY.md

Deployment notes for running perception models on target machines.

Key steps:
- Ensure drivers and CUDA are installed for GPU acceleration.
- Install onnxruntime-gpu and required python deps.
- Use tools/models/download_models.sh to fetch models listed in models_list.txt.
- Set ROBOT_PERCEPTION_MODEL_NAME to the desired model name before starting perception_node.
