# 导航指南 — B1 + B2（TF 可见 + 2D Nav Goal）

> 目标读者：高中生。读完这篇你就能在电脑上看到机器人在 RViz 里"动起来"。

---

## 前置条件

1. 已按照 [SIMULATION.md](SIMULATION.md) 完成构建，并能成功启动 `dev_sim.launch.py`。
2. 安装了 RViz2：

   ```bash
   sudo apt-get install ros-humble-rviz2
   ```

---

## 目标说明

| 目标 | 英文缩写 | 说明 |
|------|----------|------|
| **B1** | Basic Visualization | RViz 里能看到 TF 坐标系 + 机器人模型 + 里程计更新 |
| **B2** | 2D Nav Goal | 在 RViz 里点"2D Goal Pose"按钮，仿真机器人能响应并打印导航结果 |

> **注意**：这个仓库使用的是"导航骨架"（stub），不是完整的 Nav2。  
> B2 演示了导航服务调用的完整链路（Voice→NLU→Executor→NavService），  
> 但机器人在 RViz 里的 odom 坐标不会移动（固定在原点），  
> 如需机器人真正移动，需要接入完整 Nav2（见文末说明）。

---

## 步骤一：启动仿真（带 RViz）

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch robot_bringup dev_sim.launch.py rviz:=true
```

等待约 5 秒，RViz2 窗口应自动打开。

---

## 步骤二：验证 B1 — TF 树可见

### 2.1 在 RViz 里检查 TF 显示

RViz 左侧面板 → **TF** 一项已勾选 ✅（由预设的 `dev_view.rviz` 自动开启）。

你应该看到：
- 彩色坐标轴出现在 RViz 视图里，标有 `odom`、`base_footprint`、`base_link`、`lidar_link`、`camera_link`

### 2.2 用命令行验证 TF 树

打开**第二个终端**：

```bash
source /opt/ros/humble/setup.bash
source ros_ws/install/setup.bash

# 查看当前 TF 树结构（会生成 frames.pdf）
ros2 run tf2_tools view_frames
# 预期输出：odom -> base_footprint -> base_link -> lidar_link / camera_link
```

### 2.3 验证 odom 话题有数据

```bash
# 查看里程计消息（每秒约 10 次）
ros2 topic echo /odom --once
# 预期：header.frame_id = 'odom'，child_frame_id = 'base_footprint'
```

如果 TF 和 odom 都有数据，**B1 通过** ✅

---

## 步骤三：验证 B2 — 发送 2D Nav Goal

在本仿真骨架中，导航目标通过两种方式触发：

### 方式 A：通过 RViz 工具栏发送目标位姿

1. 在 RViz 工具栏，点击 **"2D Goal Pose"** 按钮（或按快捷键 `G`）。
2. 在 RViz 视图里，**点击并拖拽**，设置目标位置和方向。
3. 松开鼠标后，`/goal_pose` 话题会发出一条 `geometry_msgs/PoseStamped` 消息。

> 目前骨架中的 `nav_server_node` 监听的是 `/nav/go_handover_spot` 服务，  
> 而不是直接订阅 `/goal_pose`。  
> 下面的方式 B 会触发完整的导航服务调用链路。

### 方式 B：通过语音命令触发导航（推荐验证方式）

打开**第二个终端**，发送一条假语音指令：

```bash
source /opt/ros/humble/setup.bash
source ros_ws/install/setup.bash

# 模拟用户说"请给我递水"
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
```

然后在**第三个终端**观察响应：

```bash
source /opt/ros/humble/setup.bash
source ros_ws/install/setup.bash

# 查看 NLU 解析出的 JSON 指令（应包含 deliver_water 意图）
ros2 topic echo /nlu/command_json

# 查看执行器状态机的状态变化
ros2 topic echo /robot/state
```

**预期看到的输出**：

```
# /nlu/command_json 示例
data: '{"intent":"deliver_water","target":"user"}'

# /robot/state 示例（状态机从 IDLE 进入执行流程）
data: 'SEARCH_BOTTLE'
```

### 方式 C：直接调用导航服务

```bash
# 直接让机器人导航到"餐桌旁"
ros2 service call /nav/go_handover_spot std_srvs/srv/Trigger {}
# 预期响应：success=True，message 包含坐标信息
```

---

## 步骤四：设置 Initial Pose（初始位姿）

> 在使用完整 Nav2 时，你需要先在 RViz 里设置初始位姿。  
> 在当前骨架模式下，机器人固定在 odom 原点，可跳过此步骤。

如果将来接入完整 Nav2：
1. RViz 工具栏 → 点击 **"2D Pose Estimate"** 按钮
2. 在地图上点击你认为机器人当前的位置并拖拽设置朝向
3. 松开后，`/initialpose` 话题会发送给 Nav2 的 AMCL 节点

---

## 常见问题排查

| 症状 | 可能原因 | 解决方法 |
|------|----------|----------|
| RViz 里没有坐标轴（TF） | `fake_scan_node` 或 `robot_state_publisher` 未启动 | `ros2 node list` 检查节点是否在 |
| `/odom` 没有消息 | `base_driver_node` 未启动 | 检查 `ros2 node list`；重新运行 launch 文件 |
| 发送语音命令后无响应 | `executor_node` 或 `nlu_node` 未启动 | 检查所有节点：`ros2 node list` |
| 调用 `/nav/go_handover_spot` 返回 false | `locations.yaml` 未加载 | 检查 `locations_file` 参数是否正确 |
| Fixed Frame 选 `map` 时报错 | 没有 map→odom TF | 正常，当前仿真没有地图；改用 `odom` 作为 Fixed Frame |

---

## 接入完整 Nav2（可选）

当前骨架中的 `nav_server_node` 是一个桩（stub），只返回固定坐标，不进行真正的路径规划。  
要接入完整的 Nav2：

1. 安装 Nav2：

   ```bash
   sudo apt-get install ros-humble-navigation2 ros-humble-nav2-bringup
   ```

2. 修改 `robot_bringup/config/nav2_params.yaml`（模板已存在）。

3. 修改 `dev_sim.launch.py`，将 `nav_server_node` 替换为 Nav2 的 `nav2_bringup`。

4. 需要一张地图（用 SLAM 建图或提供静态地图）。

详细参数说明见 `ros_ws/src/robot_bringup/config/nav2_params.yaml`。

---

## 总结

- **B1 验证**：`ros2 topic echo /odom` + RViz 里看到 TF 坐标轴 → 通过
- **B2 验证**：发送语音命令 → 看到 `/robot/state` 变化 → 通过

恭喜！你已经成功验证了纯软件模式下的导航链路。 🎉
