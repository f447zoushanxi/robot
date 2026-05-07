# 家庭场景 ROS 2 Humble 机器人项目骨架

本仓库提供一个**面向家庭递水任务**的 ROS 2 Humble 项目骨架，目标是先把系统结构、接口、权限与测试方法搭好，再逐步替换真实算法与硬件驱动。

> 任务主线：`deliver_water`（找瓶子 -> 抓取 -> 导航到房间 -> 找人 -> 递交 -> 失败降级）

## 1. 硬件清单（家庭场景，30×30 底盘、可拆机械臂、15kg+承重）

### 上位机（高配笔记本）
- Ubuntu 22.04 + ROS 2 Humble
- 感知/推理：ONNX Runtime（Python）
- NLU 兜底：Ollama + Qwen2.5（结构化 JSON）

### 下位机（实时控制）
- STM32（推荐）
- 自定义串口协议（速度命令 + 编码器/急停状态回传）
- 通信超时刹车（例如 >200ms 无新指令即刹停）

### 传感器与执行器
- 2D 激光雷达：RPLIDAR A2/A3（二手可）
- 深度相机：Intel RealSense D435/D435i（二手可）
- 差速底盘（编码器）+ 电机驱动 + 电源
- 机械臂 + 夹爪（可拆快装）
- 急停按钮（硬件优先）
- 首次 owner 绑定按钮（物理确认窗口）

## 2. 软件依赖

- ROS 2 Humble（rclcpp/rclpy, Nav2, tf2）
- colcon / ament_cmake / ament_python
- Python: `numpy`, `opencv-python`, `onnxruntime`（感知路线）
- 外部语音与大模型进程（可独立于 ROS 启动）
  - ASR/TTS：外部进程桥接到 ROS topics
  - NLU 兜底：Ollama（Qwen2.5）输出 JSON

## 3. 快速开始

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

### 开发模式（仅基础节点）
```bash
ros2 launch robot_bringup dev_mode.launch.py
```

### 导航/定位模式
```bash
ros2 launch robot_bringup nav_mode.launch.py
```

## 4. 推荐运行顺序

1. 上电下位机（STM32），确认急停按钮可用
2. 启动雷达、RealSense
3. 启动 ROS 基础层（`robot_base`, `robot_safety`, `robot_voice`）
4. 启动导航（Nav2/定位）
5. 启动感知与身份模块（`robot_perception`, `robot_identity`）
6. 启动 `robot_nlu` 与 `robot_executor`
7. 人机验证：`stop`、`navigate`、`deliver_water` 流程

## 5. 首次绑定 owner（物理确认）

- 策略：**必须按下物理按钮**进入有限时间窗口（例如 30 秒）才允许执行 `EnrollOwner`
- 原因：防止家中其他人抢先绑定 owner
- 口令示例：`记住我的声音`（触发录入流程）

## 6. 权限策略

- `stop`：`any`（任何人可触发）
- `navigate/status`：`guest`（普通权限）
- `deliver_water`：`owner-only`
- `enroll_owner_voice` / `enroll_owner`：`owner-only`（首次可由物理按钮窗口放行）

## 7. 训练与数据制作建议

- ASR 自录集：家庭环境多噪声、多距离采样
- NLU 标注集：覆盖 `stop` / `navigate` / `记住我的声音` / `记住我` / `我在X`
- 瓶子图像集：厨房台面、餐桌、茶几、地面多光照采集
- 身份测试集：owner/guest 的声纹与人脸样本，统计误识率和拒识率

## 8. 测试计划入口

详细方法见：
- `docs/TESTPLAN.md`
- `docs/SEQUENCES.md`
- `docs/INTERFACES.md`
- `docs/ARCHITECTURE.md`

## 9. 无硬件模式

- `robot_base` 与 `robot_manipulation` 支持 stub/sim 参数
- 在无串口与无机械臂时也能启动，不会立刻崩溃
- `robot_perception` 提供模板服务，先走占位输出便于联调
