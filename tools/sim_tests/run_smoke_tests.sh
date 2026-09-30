#!/usr/bin/env bash
# tools/sim_tests/run_smoke_tests.sh
# Updated: also check executor status service
set -euo pipefail

REPO_ROOT=$(git rev-parse --show-toplevel)
cd "$REPO_ROOT"

source /opt/ros/humble/setup.bash || true
# build workspace (assumes developer has sourced matching ROS environment)
colcon build --symlink-install
source install/setup.bash || true

# Launch dev_sim in background and give it time to start
ros2 launch robot_bringup dev_sim.launch.py rviz:=false &
LAUNCH_PID=$!

# wait short time for nodes to come up
sleep 6

# publish a fake voice command
ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1 &

# run a short test: call a perception service if available
ros2 service call /perception/find_person robot_msgs/srv/FindPerson "{hint_name: 'owner'}" || true

# also call executor status
ros2 service call /executor/get_status std_srvs/srv/Trigger || true

# cleanup
kill $LAUNCH_PID || true
wait $LAUNCH_PID 2>/dev/null || true

echo "smoke tests finished"
