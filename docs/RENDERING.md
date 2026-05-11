# Rendering Guide — RViz Robot Visualization

This document explains how to generate a "render" of the robot model in RViz2
and save it as a screenshot.

---

## Prerequisites

1. `dev_sim.launch.py` must be running (see [SIMULATION.md](SIMULATION.md)).
2. RViz2 must be installed: `sudo apt-get install ros-humble-rviz2`.
3. A desktop environment (X11 or Wayland) is required for display.

---

## Step 1 — Launch the simulation with RViz

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch robot_bringup dev_sim.launch.py rviz:=true
```

RViz2 will open and automatically load `robot_bringup/rviz/dev_view.rviz`.

---

## Step 2 — What you should see in RViz

| Display | Description |
|---------|-------------|
| **Grid** | Grey floor grid centred at the `odom` origin |
| **RobotModel** | Grey box chassis (0.5 × 0.4 × 0.2 m) with black cylinder LiDAR on top and small blue camera at the front |
| **TF** | Coloured axes for each link: `odom`, `base_footprint`, `base_link`, `lidar_link`, `camera_link` |
| **LaserScan** | Red dots forming a ring ~5 m from the robot |
| **Odometry** | Arrow at the robot origin showing velocity direction |

> If nothing appears, ensure all nodes are running:
> ```bash
> ros2 node list
> # Expected: /robot_state_publisher /fake_scan_node /base_driver_node …
> ```

---

## Step 3 — Adjust the view

- **Orbit**: left-click and drag
- **Pan**: middle-click (or Shift + left-click) and drag
- **Zoom**: scroll wheel

A good starting view: orbit to a 45° top-front angle so you can see
the chassis, LiDAR cylinder, camera box, and the laser ring.

---

## Step 4 — Take a screenshot

### Option A — System screenshot tool (simplest)

Press `PrtSc` (or your system's screenshot shortcut) to capture the whole screen,
then crop to the RViz window.

### Option B — RViz built-in export

In the RViz menu bar: **File → Export → Screenshot…**

Save as `robot_render.png` (or any name you choose).

### Option C — Command-line (headless / CI)

```bash
# Install scrot if needed
sudo apt-get install scrot

# Wait for RViz to fully load (≈5 s), then capture
sleep 5 && scrot robot_render.png -u
```

---

## Step 5 — Save the RViz configuration (optional)

If you customise the view or add displays, save your layout for reuse:

**File → Save Config As…** → save to `ros_ws/src/robot_bringup/rviz/my_view.rviz`

Then reference it in a launch file:

```python
arguments=['-d', '/path/to/my_view.rviz']
```

---

## Robot Model Details

The URDF is located at:
```
ros_ws/src/robot_description/urdf/robot.urdf.xacro
```

TF tree:
```
odom
 └── base_footprint   (dynamic: broadcast by fake_scan_node)
       └── base_link  (fixed +0.1 m up)
             ├── lidar_link   (fixed +0.2 m up from base_link)
             └── camera_link  (fixed +0.25 m forward, +0.1 m up from base_link)
```

To view the raw URDF XML after xacro processing:

```bash
source ros_ws/install/setup.bash
xacro ros_ws/src/robot_description/urdf/robot.urdf.xacro
```

---

## Improving the Model

The current model uses simple geometric primitives (boxes, cylinders).
To add real mesh visuals:

1. Export mesh files (`.stl` or `.dae`) from a CAD tool.
2. Place them in `ros_ws/src/robot_description/meshes/`.
3. Replace `<box>` / `<cylinder>` geometry in `robot.urdf.xacro` with:

```xml
<geometry>
  <mesh filename="package://robot_description/meshes/chassis.stl" scale="0.001 0.001 0.001"/>
</geometry>
```

4. Rebuild: `colcon build --packages-select robot_description`.
