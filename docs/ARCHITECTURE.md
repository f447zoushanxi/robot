# 系统架构（家庭场景）

## 1. 分层

1. **下位机（STM32）**
   - 负责电机闭环、编码器、急停输入
   - 自定义串口协议与上位机通信

2. **上位机 ROS2 中间层**
   - `robot_base`: 串口驱动 + `/cmd_vel` -> 里程计
   - `robot_safety`: 急停优先、限速、必要时清零速度

3. **任务与智能层**
   - `robot_voice`: 语音桥接（ASR/TTS 可外部）
   - `robot_nlu`: 规则优先 + Ollama(Qwen2.5) JSON 兜底
   - `robot_executor`: deliver_water 状态机
   - `robot_identity`: owner/guest/unknown 判定与权限门控

4. **导航与感知执行层**
   - `robot_nav`: 地点库 + 导航封装
   - `robot_perception`(Python): bottle/person 感知服务
   - `robot_manipulation`: 抓取与递交动作接口

## 2. 数据流（主路径）

1. `/voice/asr_text` -> `robot_nlu` -> `/nlu/command_json`
2. `robot_executor` 读取命令后先进行权限检查（owner-only/guest/any）
3. 若是 `deliver_water`：
   - `robot_perception/detect_bottle`
   - `robot_manipulation/pick_bottle`
   - `robot_nav` 导航到用户房间
   - `robot_perception/find_person`
   - `robot_manipulation/hand_over`
4. 任一步失败触发重试/降级：前往客厅交付点

## 3. 权限模型

- owner-only: `deliver_water`, `enroll_owner(_voice)`
- any: `stop`
- guest: 常规导航/状态查询
- 首次 owner 绑定：必须物理按钮窗口放行

## 4. 感知路线

- RealSense D435/D435i: 彩色 + 对齐深度 + 相机内参
- ONNX Runtime 推理接口（当前为 stub）
- 深度中值滤波 + 像素反投影 + tf2 到 `base_link`

## 5. 关键硬件约束（与前述讨论一致）

- 底盘尺寸约 30×30
- 承重 15kg+
- 机械臂可拆卸
- 家庭地面：瓷砖 + 木地板混合
- 雷达：RPLIDAR A2/A3（二手）
- 深度相机：RealSense D435/D435i（二手）
