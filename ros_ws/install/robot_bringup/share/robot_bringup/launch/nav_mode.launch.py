# Copyright 2026 f447zoushanxi.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
#
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from pathlib import Path


def generate_launch_description():
    share = Path(get_package_share_directory('robot_bringup'))
    locations = str(share / 'config' / 'locations.yaml')

    return LaunchDescription([
        Node(
            package='robot_base',
            executable='base_driver_node',
            name='base_driver_node',
            parameters=[{'use_stub': True, 'cmd_timeout_ms': 200}],
            output='screen',
        ),
        Node(
            package='robot_safety',
            executable='safety_node',
            name='safety_node',
            output='screen',
        ),
        Node(
            package='robot_nav',
            executable='nav_server_node',
            name='nav_server_node',
            parameters=[{'locations_file': locations, 'handover_spot': '餐桌旁'}],
            output='screen',
        ),
        Node(
            package='robot_perception',
            executable='perception_node',
            name='perception_node',
            output='screen',
        ),
        Node(
            package='robot_identity',
            executable='identity_node',
            name='identity_node',
            output='screen',
        ),
        Node(
            package='robot_manipulation',
            executable='manipulation_node',
            name='manipulation_node',
            parameters=[{'sim_mode': True}],
            output='screen',
        ),
        Node(
            package='robot_voice',
            executable='voice_bridge_node',
            name='voice_bridge_node',
            output='screen',
        ),
        Node(
            package='robot_nlu',
            executable='nlu_node',
            name='nlu_node',
            output='screen',
        ),
        Node(
            package='robot_executor',
            executable='executor_node',
            name='executor_node',
            output='screen',
        ),
    ])
