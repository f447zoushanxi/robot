# 语音→NLU→执行器 端对端测试指南

> 目标读者：高中生。没有麦克风？没关系，用命令行发"假语音"就能测试整个流程！

---

## 这个流程是什么？

```
你说话 → 麦克风 → 语音识别(ASR) → robot_voice → robot_nlu → robot_executor → 执行动作
```

在纯软件测试时，我们跳过麦克风和 ASR，直接从"文字"开始注入：

```
你发命令 → /voice/raw_text 话题 → robot_voice → robot_nlu → robot_executor → 执行动作
```

---

## 前置条件

已完成构建（参见 [SIMULATION.md](SIMULATION.md)）：

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

---

## 步骤一：启动系统

```bash
# 终端 1：启动完整仿真系统（不需要 RViz）
ros2 launch robot_bringup dev_sim.launch.py
```

等待所有节点启动（约 3～5 秒），你会看到每个节点打印 "started" 或就绪信息。

---

## 步骤二：确认关键节点都在运行

打开**终端 2**：

```bash
source /opt/ros/humble/setup.bash && source ros_ws/install/setup.bash
ros2 node list
```

**预期看到的节点**（最少应有这些）：

```
/voice_bridge_node    ← 语音桥接
/nlu_node             ← 自然语言理解
/executor_node        ← 任务状态机
/identity_node        ← 身份识别
/nav_server_node      ← 导航服务
/manipulation_node    ← 机械臂服务
/perception_node      ← 感知服务
/base_driver_node     ← 底盘驱动（stub）
/fake_scan_node       ← 假激光扫描
/robot_state_publisher← 机器人模型发布
```

---

## 步骤三：订阅关键话题（观察输出）

打开**终端 3**，订阅 NLU 输出：

```bash
source /opt/ros/humble/setup.bash && source ros_ws/install/setup.bash
ros2 topic echo /nlu/command_json
```

打开**终端 4**，订阅执行器状态：

```bash
source /opt/ros/humble/setup.bash && source ros_ws/install/setup.bash
ros2 topic echo /robot/state
```

---

## 步骤四：发送假语音命令

打开**终端 5**，发布测试消息：

```bash
source /opt/ros/humble/setup.bash && source ros_ws/install/setup.bash

# 测试命令 1：递水
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1

# 稍等 1～2 秒后，测试命令 2：再发一次（可选）
# ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我倒水'}" -1
```

---

## 步骤五：验证输出

### 终端 3（/nlu/command_json）预期输出：

```
data: '{"intent":"deliver_water","target":"user"}'
---
```

这说明 NLU 节点成功把"请给我递水"解析成了结构化指令。

### 终端 4（/robot/state）预期输出序列：

```
data: 'IDLE'
---
data: 'SEARCH_BOTTLE'
---
data: 'PICK_BOTTLE'
---
...
```

这说明执行器状态机收到了 NLU 指令，并开始执行递水任务的流程。

---

## 话题/服务速查表

| 话题 / 服务 | 类型 | 方向 | 说明 |
|-------------|------|------|------|
| `/voice/raw_text` | `std_msgs/String` | 你→系统 | 注入测试语音文字（无麦克风时使用） |
| `/voice/asr_text` | `std_msgs/String` | voice→nlu | voice_bridge_node 转发的 ASR 文本 |
| `/nlu/command_json` | `std_msgs/String` | nlu→executor | NLU 解析结果（JSON 格式） |
| `/robot/state` | `std_msgs/String` | executor→外部 | 执行器当前状态 |
| `/cmd_vel` | `geometry_msgs/Twist` | executor→base | 速度指令 |
| `/odom` | `nav_msgs/Odometry` | base→all | 里程计（stub 固定在原点） |
| `/scan` | `sensor_msgs/LaserScan` | sim→all | 合成激光扫描数据 |
| `/identity/enroll_owner` | `robot_msgs/EnrollOwner` (srv) | 外部→identity | Owner 绑定服务 |
| `/nav/go_handover_spot` | `std_srvs/Trigger` (srv) | executor→nav | 导航到交付点服务 |

---

## 测试更多语音命令

NLU 节点（`robot_nlu/src/nlu_parser.cpp`）支持以下关键词触发 `deliver_water` 意图：

| 你说的话 | NLU 解析意图 |
|---------|-------------|
| 请给我递水 | `deliver_water` |
| 请给我倒水 | `deliver_water` |
| 帮我拿水 | `deliver_water` |

要添加新的意图或命令词，编辑 `ros_ws/src/robot_nlu/src/nlu_parser.cpp`，  
然后重新构建：`colcon build --packages-select robot_nlu`。

---

## 常见问题

| 症状 | 原因 | 解决方法 |
|------|------|----------|
| `/nlu/command_json` 没有消息 | `nlu_node` 未启动，或 `voice_bridge_node` 未转发 | 检查 `ros2 node list`；确认 `voice_bridge_node` 在列 |
| `/robot/state` 一直是 `IDLE` | `executor_node` 未收到 NLU 消息 | 检查 `/voice/asr_text` 话题是否有消息：`ros2 topic echo /voice/asr_text` |
| 发送命令后无任何反应 | 节点没全部启动 | 等待更长时间再试；检查终端 1 是否有报错 |
| NLU 输出 `unknown` 意图 | 命令词不在 NLU 规则里 | 修改 `nlu_parser.cpp` 添加新规则 |

---

## 一键验证脚本

以下命令可以快速验证整个端到端流程是否正常（在系统启动后执行）：

```bash
# 启动系统后，在新终端运行：
source /opt/ros/humble/setup.bash && source ros_ws/install/setup.bash

# 1. 订阅 NLU 输出（后台）
ros2 topic echo /nlu/command_json &
NLU_PID=$!

# 2. 订阅执行器状态（后台）
ros2 topic echo /robot/state &
STATE_PID=$!

# 3. 发送测试命令
sleep 1
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1

# 4. 等待响应
sleep 3

# 5. 清理后台订阅
kill $NLU_PID $STATE_PID 2>/dev/null
```
