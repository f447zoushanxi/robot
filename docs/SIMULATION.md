# Simulation Guide — Pure-Software Development

This document explains how to run the robot stack **entirely in software** —
no physical chassis, LiDAR, camera, or microphone required.

---

## Goals

| Goal | Description |
|------|-------------|
| **A** | RViz robot model rendering (RobotModel + TF tree) |
| **B** | Basic navigation in mock mode (fake odometry, fake laser scan, stub Nav server) |
| **C** | End-to-end voice(text) → NLU → executor loop using simulated inputs |

---

## Package Map

| Package | Role in Simulation |
|---------|--------------------|
| `robot_description` | URDF/Xacro model — loaded by `robot_state_publisher` to publish static TF and `/robot_description` |
| `robot_sim` | `fake_scan_node` — publishes synthetic `/scan` and broadcasts `odom→base_footprint` TF |
| `robot_base` | `base_driver_node` (use_stub=true) — publishes `/odom` and `/estop`; subscribes `/cmd_vel` |
| `robot_nav` | `nav_server_node` — stub navigation service using `locations.yaml` |
| `robot_voice` | `voice_bridge_node` — forwards `/voice/raw_text` as ASR text |
| `robot_nlu` | `nlu_node` — parses text to JSON commands |
| `robot_identity` | `identity_node` — stub identity recognition |
| `robot_manipulation` | `manipulation_node` (sim_mode=true) — stub arm control |
| `robot_perception` | `perception_node` (stub) — fake bottle/person detection |
| `robot_executor` | `executor_node` — task state machine |
| `robot_bringup` | Launch files, config, RViz config |

### What IS simulated (no hardware needed)
- Robot model in RViz (`robot_state_publisher` + URDF)
- TF tree: `odom → base_footprint → base_link → lidar_link / camera_link`
- Laser scan (`/scan`) — 360-degree synthetic ring, all ranges = 5 m
- Odometry (`/odom`) — stationary at origin
- Voice input — injected by publishing to `/voice/raw_text`
- Navigation goal result — stub returns success with coordinates from `locations.yaml`
- Arm / perception — stub services that return canned success responses

### What is NOT simulated (requires hardware or real Nav2)
- Real sensor data (actual LiDAR point clouds, camera images)
- Real movement (the robot does not physically move; odometry stays at origin)
- Full Nav2 path planning / SLAM — `nav_server_node` is a stub that does not use Nav2
- Speech recognition (ASR) hardware — use `/voice/raw_text` injection instead

---

## Prerequisites

```bash
# ROS 2 Humble + required packages (see CI workflow for the full list)
sudo apt-get install -y \
  ros-humble-robot-state-publisher \
  ros-humble-xacro \
  ros-humble-tf2-ros
```

---

## Quick Start

```bash
# 1. Clone and enter the workspace
cd ros_ws

# 2. Build (first time or after changes)
source /opt/ros/humble/setup.bash
colcon build --symlink-install

# 3. Source the workspace
source install/setup.bash

# 4. Launch the simulation (without RViz)
ros2 launch robot_bringup dev_sim.launch.py

# — or with RViz —
ros2 launch robot_bringup dev_sim.launch.py rviz:=true
```

---

## Sending a Fake Voice Command (Goal C)

Open a **second terminal**:

```bash
source /opt/ros/humble/setup.bash
source ros_ws/install/setup.bash

# Simulate the user saying "请给我递水" (bring me water)
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
```

Watch the pipeline respond:

```bash
# NLU output (should contain deliver_water intent)
ros2 topic echo /nlu/command_json

# Executor state machine transitions
ros2 topic echo /robot/state
```

---

## Checking the TF Tree (Goal A)

```bash
# Print the TF tree to console
ros2 run tf2_tools view_frames
# Opens frames.pdf showing: odom -> base_footprint -> base_link -> lidar_link / camera_link

# Or live echo
ros2 topic echo /tf
ros2 topic echo /tf_static
```

---

## Checking the Fake Laser Scan (Goal B)

```bash
ros2 topic echo /scan --once
# Expect: frame_id='lidar_link', ~360 ranges all ≈ 5.0 m
```

---

## Running the Integration Tests

```bash
cd ros_ws
colcon test --packages-select robot_bringup --event-handlers console_direct+
colcon test-result --verbose
```

The `dev_sim.launch.test.py` test checks:
1. `robot_state_publisher`, `fake_scan_node`, `base_driver_node` nodes start
2. `/scan` topic delivers data with `frame_id='lidar_link'`
3. `/odom` topic delivers data with `frame_id='odom'`

---

## Troubleshooting

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| `Package 'robot_description' not found` | Not built yet | `colcon build` then `source install/setup.bash` |
| `robot_state_publisher` not found | Package not installed | `sudo apt-get install ros-humble-robot-state-publisher` |
| `xacro` command not found | xacro not installed | `sudo apt-get install ros-humble-xacro` |
| `/scan` has no messages | `fake_scan_node` crashed | Check `ros2 node list`; re-run `dev_sim.launch.py` |
| RViz shows no robot model | URDF not loaded | Ensure `/robot_description` topic has data: `ros2 topic echo /robot_description` |
| `tf2_ros` import error | Python tf2_ros not installed | `sudo apt-get install ros-humble-tf2-ros` |

---

## Expanding the Simulation

- **Real Nav2**: Replace `nav_server_node` stub with a full Nav2 stack.
  Configure it to use `/scan` (from `fake_scan_node`) and `/odom` (from `base_driver_node`).
- **Moving robot**: Modify `fake_scan_node` to update the `odom→base_footprint` TF over time
  based on a velocity subscriber.
- **Custom voice commands**: Edit `robot_nlu/src/nlu_parser.cpp` to add new intents,
  then send them via `/voice/raw_text`.
