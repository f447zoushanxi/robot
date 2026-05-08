# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 模块说明：robot_bringup — 导航模式启动文件（nav_mode.launch.py）
# =============================================================================
# 这个 launch 文件在 dev_mode 的基础上额外启动了导航服务节点（robot_nav），
# 并从 locations.yaml 加载家庭地点信息。
#
# 与 dev_mode.launch.py 的区别：
#   - 额外启动 nav_server_node（导航服务）
#   - 从 robot_bringup 包的 config/locations.yaml 加载地点列表
#   - 配置了 handover_spot（交付点名称）为"餐桌旁"
#
# 运行方式：
#   cd ros_ws && source install/setup.bash
#   ros2 launch robot_bringup nav_mode.launch.py
#
# 需要先准备：
#   - ros_ws/src/robot_bringup/config/locations.yaml（地点配置文件）
#   - 文件格式见 robot_nav 模块文档
# =============================================================================

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from pathlib import Path


def generate_launch_description():
    """生成 launch 描述，包含导航服务节点"""
    # 获取 robot_bringup 包安装后的共享目录（install/robot_bringup/share/）
    share = Path(get_package_share_directory('robot_bringup'))
    # 拼接 locations.yaml 的完整路径
    locations = str(share / 'config' / 'locations.yaml')

    return LaunchDescription([
        # 底盘驱动节点（同 dev_mode）
        Node(
            package='robot_base',
            executable='base_driver_node',
            name='base_driver_node',
            parameters=[{'use_stub': True, 'cmd_timeout_ms': 200}],
            output='screen',
        ),
        # 安全节点（同 dev_mode）
        Node(
            package='robot_safety',
            executable='safety_node',
            name='safety_node',
            output='screen',
        ),
        # 导航服务节点（nav_mode 独有）：
        # - locations_file：加载家庭地点坐标
        # - handover_spot：指定"递水交付点"为"餐桌旁"
        Node(
            package='robot_nav',
            executable='nav_server_node',
            name='nav_server_node',
            parameters=[{'locations_file': locations, 'handover_spot': '餐桌旁'}],
            output='screen',
        ),
        # 感知节点（同 dev_mode）
        Node(
            package='robot_perception',
            executable='perception_node',
            name='perception_node',
            output='screen',
        ),
        # 身份识别节点（同 dev_mode）
        Node(
            package='robot_identity',
            executable='identity_node',
            name='identity_node',
            output='screen',
        ),
        # 机械臂节点（同 dev_mode，sim_mode=True）
        Node(
            package='robot_manipulation',
            executable='manipulation_node',
            name='manipulation_node',
            parameters=[{'sim_mode': True}],
            output='screen',
        ),
        # 语音桥接节点（同 dev_mode）
        Node(
            package='robot_voice',
            executable='voice_bridge_node',
            name='voice_bridge_node',
            output='screen',
        ),
        # NLU 节点（同 dev_mode）
        Node(
            package='robot_nlu',
            executable='nlu_node',
            name='nlu_node',
            output='screen',
        ),
        # 执行器节点（同 dev_mode）
        Node(
            package='robot_executor',
            executable='executor_node',
            name='executor_node',
            output='screen',
        ),
    ])
