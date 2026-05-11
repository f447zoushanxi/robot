# Documentation Index

Welcome to the home-robot project documentation.

---

## Pure-Software Development (No Hardware Required)

The project supports a **pure-software simulation mode** that lets you develop and test the full
robot stack on any laptop — no chassis, no LiDAR, no camera, no microphone needed.

### Goals

| Goal | Status |
|------|--------|
| **A** RViz robot model rendering (RobotModel + TF tree) | ✅ Supported via `robot_description` + `robot_sim` |
| **B** Basic navigation in mock mode | ✅ Stub nav via `robot_nav` (`nav_server_node`) |
| **C** Voice(text) → NLU → executor loop | ✅ Inject via `/voice/raw_text` topic |

### Quick Start

```bash
cd ros_ws && source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
ros2 launch robot_bringup dev_sim.launch.py rviz:=true
```

Send a fake voice command (second terminal):

```bash
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
```

---

## Guides

| Guide | Description |
|-------|-------------|
| [SIMULATION.md](SIMULATION.md) | Pure-software workflow, commands, package map, troubleshooting |
| [RENDERING.md](RENDERING.md) | How to generate the RViz robot model screenshot ("render") |
| [NAVIGATION.md](NAVIGATION.md) | B1+B2: verify TF/odom, set initial pose, send 2D Nav Goal |
| [VOICE_NLU_EXECUTOR.md](VOICE_NLU_EXECUTOR.md) | End-to-end voice→NLU→executor loop without hardware |
| [ARCHITECTURE.md](ARCHITECTURE.md) | Overall system architecture and package descriptions |
| [INTERFACES.md](INTERFACES.md) | ROS2 topic / service / action interface reference |
| [SEQUENCES.md](SEQUENCES.md) | Message sequence diagrams for key workflows |
| [TESTPLAN.md](TESTPLAN.md) | Test strategy and how to run tests |
| [INTEGRATION_TESTS.md](INTEGRATION_TESTS.md) | Beginner-friendly guide for the new CI integration tests |
| [BEGINNER_GUIDE.md](BEGINNER_GUIDE.md) | Step-by-step guide for newcomers |
| [assets/README.md](assets/README.md) | Screenshot placeholder and rendering instructions |

---

## Package Overview (Simulation Perspective)

```
ros_ws/src/
├── robot_description   ← URDF robot model (NEW — visualization)
├── robot_sim           ← Fake sensor nodes: /scan + TF broadcaster (NEW)
├── robot_bringup       ← Launch files (dev_mode, dev_sim, nav_mode) + RViz config
├── robot_base          ← Chassis driver (use_stub=true → fake odometry)
├── robot_nav           ← Navigation stub (locations.yaml)
├── robot_voice         ← Voice bridge (inject via /voice/raw_text)
├── robot_nlu           ← NLU parser (text → JSON command)
├── robot_identity      ← Identity recognition stub
├── robot_manipulation  ← Arm control stub (sim_mode=true)
├── robot_perception    ← Perception stub (fake detect/find)
├── robot_executor      ← Task state machine
├── robot_safety        ← Velocity safety / estop
└── robot_msgs          ← Shared message / service / action definitions
```
