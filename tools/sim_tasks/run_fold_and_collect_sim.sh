#!/usr/bin/env bash
# tools/sim_tasks/run_fold_and_collect_sim.sh
# A small helper that starts the sim (bringup), starts executor task and publishes a fake detection
set -euo pipefail

REPO_ROOT=$(git rev-parse --show-toplevel)
cd "$REPO_ROOT"

source /opt/ros/humble/setup.bash || true
colcon build --symlink-install || true
source install/setup.bash || true

# Launch bringup in background
ros2 launch robot_bringup dev_sim.launch.py rviz:=false &
PID=$!
sleep 6

# start executor
ros2 service call /executor/start_task std_srvs/srv/Trigger "{}" || true
# publish fake detection
ros2 topic pub /perception/detections_text std_msgs/msg/String "{data: 'yolov8:bottle:0.95'}" -1 || true

# wait for executor to process
sleep 8
# fetch status
ros2 service call /executor/get_status std_srvs/srv/Trigger "{}" || true

# cleanup
kill $PID || true
wait $PID 2>/dev/null || true

echo "fold_and_collect_sim finished"
