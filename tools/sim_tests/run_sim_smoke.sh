#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${REPO_ROOT}/ros_ws"
source /opt/ros/humble/setup.bash
colcon build --symlink-install --event-handlers console_direct+
colcon test --event-handlers console_direct+
colcon test-result --verbose
