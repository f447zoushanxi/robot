# 集成测试说明（新手版）

这份文档解释一个关键问题：  
**机器人各个节点放在一起后，数据链路真的能跑通吗？**

我们新增的 CI 集成测试会自动验证这条链路：

1. 向 `/voice/asr_text` 发一句中文文本（模拟语音识别结果）
2. 观察 `/nlu/command_json` 是否输出正确意图
3. 观察 `/robot/state` 是否有新状态消息（证明执行器在运行）

---

## 测试覆盖了什么

在 `dev_mode.launch.py` 下，测试会检查：

- `"请给我递水"` -> NLU JSON 包含 `deliver_water`
- `"立刻停下"` -> NLU JSON 包含 `stop`
- 每条命令后 `/robot/state` 都会有新消息

这说明 **C 链路（文本/语音 -> NLU -> 执行器）** 在纯软件环境可用，不需要硬件。

---

## 本地怎么运行

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
colcon build --event-handlers console_direct+
colcon test --packages-select robot_bringup robot_nlu --event-handlers console_direct+ --ctest-args -VV --output-on-failure
colcon test-result --verbose
```

---

## 失败了怎么看

先看 `colcon test-result --verbose`，重点关注这两个测试文件：

- `robot_bringup/test/dev_mode.launch.test.py`
- `robot_nlu/test/test_nlu_parser.cpp`

常见原因：

- 启动超时：CI 机器较慢，节点没在超时内出现在图里
- 话题名写错：例如把 `/voice/asr_text` 写成别的名字
- 意图不匹配：NLU 规则改了，但测试还在用旧的期望值

如果你是第一次接触 ROS2，可以先手动验证：

```bash
ros2 launch robot_bringup dev_mode.launch.py
```

另开终端：

```bash
source /opt/ros/humble/setup.bash
source ros_ws/install/setup.bash
ros2 topic pub --once /voice/asr_text std_msgs/msg/String "{data: '请给我递水'}"
ros2 topic echo /nlu/command_json
ros2 topic echo /robot/state
```
