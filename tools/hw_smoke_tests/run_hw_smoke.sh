#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${REPO_ROOT}/ros_ws"
source /opt/ros/humble/setup.bash
colcon build --symlink-install --event-handlers console_direct+
source install/setup.bash

echo "[HW SMOKE] launching bringup in hardware-oriented mode..."
ros2 launch robot_bringup dev_mode.launch.py
