# ROS2 接口说明

## 1. Topics

| 名称 | 类型 | 发布方 -> 订阅方 | 字段/含义 |
|---|---|---|---|
| `/cmd_vel` | `geometry_msgs/msg/Twist` | safety/executor -> base | `linear.x`前进速度(m/s), `angular.z`角速度(rad/s) |
| `/odom` | `nav_msgs/msg/Odometry` | base -> nav/executor | 机器人里程计位姿与速度 |
| `/estop` | `std_msgs/msg/Bool` | base/safety -> 全局 | `true`代表急停生效 |
| `/voice/asr_text` | `std_msgs/msg/String` | voice(ASR桥接) -> nlu | 识别后的文本 |
| `/nlu/command_json` | `std_msgs/msg/String` | nlu -> executor | JSON命令字符串 |
| `/identity/current_role` | `std_msgs/msg/String` | identity -> executor | `owner/guest/unknown` |
| `/camera/color/image_raw` | `sensor_msgs/msg/Image` | camera -> perception | RGB图像 |
| `/camera/aligned_depth_to_color/image_raw` | `sensor_msgs/msg/Image` | camera -> perception | 对齐深度图 |
| `/camera/color/camera_info` | `sensor_msgs/msg/CameraInfo` | camera -> perception | 相机内参 |

## 2. Services

### 2.1 robot_msgs

#### `/perception/detect_bottle` -> `robot_msgs/srv/DetectObject`
- Request
  - `string object_name`: 目标名，默认 `bottle`
  - `float32 timeout_sec`: 超时时间
- Response
  - `bool found`: 是否找到
  - `geometry_msgs/Point position`: base_link坐标系下目标中心点
  - `float32 confidence`: 置信度
  - `string frame_id`: 输出坐标系，默认 `base_link`
  - `string message`: 调试信息

#### `/perception/find_person` -> `robot_msgs/srv/FindPerson`
- Request
  - `string hint_name`: 可选提示（owner/guest）
  - `float32 timeout_sec`: 超时时间
- Response
  - `bool found`: 是否找到
  - `geometry_msgs/Point position`: 人体中心点
  - `float32 confidence`: 置信度
  - `string identity`: `owner/guest/unknown`
  - `string message`: 调试说明

#### `/identity/enroll_owner` -> `robot_msgs/srv/EnrollOwner`
- Request
  - `bool require_physical_confirm`: 是否要求物理确认
  - `float32 window_sec`: 物理确认有效窗口
- Response
  - `bool accepted`: 是否允许进入录入
  - `string owner_id`: 绑定后的owner标识
  - `string message`: 结果说明

### 2.2 其他基础服务

| 名称 | 类型 | 说明 |
|---|---|---|
| `/identity/recognize_owner` | `std_srvs/srv/Trigger` | 返回当前识别角色（通过`message`字段） |
| `/manipulation/pick_bottle` | `std_srvs/srv/Trigger` | 触发抓取占位动作 |
| `/manipulation/hand_over` | `std_srvs/srv/Trigger` | 触发递交占位动作 |
| `/nav/go_handover_spot` | `std_srvs/srv/Trigger` | 导航到交付点（占位） |

## 3. Actions（预留）

### `robot_msgs/action/PickBottle`
- Goal: `string object_name`
- Result: `bool success`, `string message`
- Feedback: `string stage`

### `robot_msgs/action/HandOver`
- Goal: `string target_identity`
- Result: `bool success`, `string message`
- Feedback: `string stage`

> 当前实现以 service 为主，action 已预留便于后续替换为可中断长任务。
