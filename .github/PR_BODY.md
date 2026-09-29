feat: AI interfaces, CI, models & training/bench/sim scaffolds

本 PR 在 feature/ai-interfaces-ci 分支上一次性引入机器人开发的 AI/感知与测试骨架，目标是为后续把真实模型、感知、任务执行与硬件联调做准备。主要变更与目的如下：

改动摘要
- CI: 新增 .github/workflows/ci.yml（colcon build + colcon test 基础流水线）
- ROS interfaces: 新增 ros_ws/src/robot_ai_interfaces 消息包（Object/Person/Route/DetectionArray）
- C++: 新增 ros_ws/src/robot_ai C++ package（生命周期节点骨架 + onnx_wrapper stub）
- Perception: 更新 ros_ws/src/robot_perception/perception_node.py，加入 ModelManager/可选 ONNX 推理支持
- 模型管理: ros_ws/src/robot_perception/models/models_list.txt 与 tools/models/download_models.sh（支持 hf:owner/repo 与 http(s)）
- 训练/数据: tools/train/*（data_prep.py/train_yolov8.sh/export_onnx.sh/quantize.sh）
- 数据抽取/转换: tools/data/{extract_images_from_bag.py, convert_to_yolo.py}
- 仿真/测试: tools/sim_tests/run_smoke_tests.sh, tests/integration/launch_test_deliver_water.py
- Benchmark: tools/bench_inference.py
- docs: docs/TRAINING.md, docs/DEPLOY.md, docs/ROADMAP_OPTIMIZATION.md
- pre-commit: .pre-commit-config.yaml

为何这样做（要点）
- 统一消息接口（robot_ai_interfaces）使 C++/Python 跨模块通信高效且类型安全。  
- 模型按 URL 管理（不将大模型入仓），并提供 HF/HTTP 下载脚本，方便在本地或 CI（自托管）拉取并比较多个模型（DeepSeek、YOLOv8n、ONNX-Zoo SSD）。  
- 默认本地训练模型为 YOLOv8n（轻量、易训练、可导出 ONNX）；DeepSeek 作为视觉–语言对比线，支持语义检索任务。  
- 提供训练/导出/量化/bench/仿真脚本，帮助从数据采集→训练→导出→部署建立端到端流程。

如何在本地一键跑通（摘要）
1. 环境：
   python3 -m venv ~/robot-env && source ~/robot-env/bin/activate  
   pip install -U pip  
   pip install ultralytics onnxruntime-gpu opencv-python huggingface-hub

2. 构建 ROS2 工作区：
   source /opt/ros/humble/setup.bash  
   cd ros_ws  
   colcon build --symlink-install  
   source install/setup.bash

3. 下载示例模型（可选）：
   bash ros_ws/src/robot_perception/models/download_models.sh

4. 选择模型并运行感知节点或仿真：
   export ROBOT_PERCEPTION_MODEL_NAME=yolov8_local  
   ros2 launch robot_bringup dev_sim.launch.py rviz:=false  
   或 ros2 run robot_perception perception_node

5. 运行 smoke test（快速健康检查）：
   bash tools/sim_tests/run_smoke_tests.sh

验收清单（自动/手动）
- [ ] colcon build 在 Ubuntu 22.04 + ROS 2 Humble 下成功（CI 运行）  
- [ ] perception_node 在无模型依赖的情况下以 stub 方式正常启动（回退路径）  
- [ ] tools/sim_tests/run_smoke_tests.sh 启动仿真并能调用 /perception/find_person（不抛异常）  
- [ ] 模型下载脚本能成功下载 HF/HTTP 模型到 ros_ws/src/robot_perception/models/（在本地测试）  
- [ ] tools/bench_inference.py 能对 ONNX 模型运行基准并输出延迟统计（在你的 RTX4060 上运行）  
- [ ] docs/TRAINING.md 和 docs/DEPLOY.md 能指导工程师完成训练/导出/部署步骤

注意事项与 CI 建议
- Heavy GPU tests（模型基准/出口验证）不要在 GitHub-hosted runners 上执行，建议在自托管 runner（有 GPU）上运行。当前 CI 仅做构建 + 单元测试 + 基础 smoke 测试（无 GPU 假设）。
- 模型二进制不放入 Git 仓库以避免膨胀；使用 models_list.txt 下载与本地 file:// 路径支持。

后续行动（我会做）
- 在 PR 创建后我会贴上 PR 链接、运行日志样例、并在 PR body 中附上快速验收步骤与 CI 说明。  
- 收到你的 Review 后我会根据反馈将 lifecycle 节点补全、把 onnx_wrapper 用 ONNXRuntime 替换并添加 CUDA provider 检测/回退逻辑、集成 identity（face/voice）、并实现叠衣/捡垃圾动作序列的仿真验证脚本。
