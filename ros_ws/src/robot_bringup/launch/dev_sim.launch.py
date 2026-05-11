# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 模块说明：robot_bringup — 纯软件仿真启动文件（dev_sim.launch.py）
# =============================================================================
# 这个 launch 文件以"纯软件模式"启动整个系统，不需要任何硬件。
#
# 启动的节点：
#   A. 可视化 (RViz / TF 树)：
#      - robot_state_publisher：读取 URDF 发布静态 TF（base_footprint->base_link 等）
#      - fake_scan_node       ：发布合成 /scan + TF odom->base_footprint
#      - rviz2 (可选)         ：打开 RViz，rviz:=true 时才启动
#
#   B. 导航相关：
#      - base_driver_node     ：底盘驱动（use_stub=True），发布 /odom + /estop
#      - nav_server_node      ：导航服务（locations.yaml stub 模式）
#
#   C. 语音→NLU→执行器闭环：
#      - voice_bridge_node    ：语音桥接（手动发 /voice/raw_text 模拟语音）
#      - nlu_node             ：语言理解
#      - identity_node        ：身份识别
#      - manipulation_node    ：机械臂（sim_mode=True）
#      - perception_node      ：感知（stub 模式）
#      - executor_node        ：任务执行状态机
#
# 启动方式：
#   cd ros_ws && source install/setup.bash
#   ros2 launch robot_bringup dev_sim.launch.py           # 不打开 RViz
#   ros2 launch robot_bringup dev_sim.launch.py rviz:=true # 打开 RViz
#
# 发送假语音指令（另开终端）：
#   ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
#
# 观察状态：
#   ros2 topic echo /robot/state
#   ros2 topic echo /scan
# =============================================================================

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    """生成仿真模式的 launch 描述。"""

    # --- launch 参数 ---
    rviz_arg = DeclareLaunchArgument(
        'rviz',
        default_value='false',
        description='Set true to launch RViz2 for visualization',
    )

    # --- 机器人 URDF 路径 ---
    urdf_path = PathJoinSubstitution(
        [FindPackageShare('robot_description'), 'urdf', 'robot.urdf.xacro']
    )
    robot_description = ParameterValue(
        Command(['xacro ', urdf_path]),
        value_type=str,
    )

    # --- RViz 配置路径 ---
    rviz_config = PathJoinSubstitution(
        [FindPackageShare('robot_bringup'), 'rviz', 'dev_view.rviz']
    )

    # --- locations.yaml 路径 ---
    bringup_share = Path(get_package_share_directory('robot_bringup'))
    locations_file = str(bringup_share / 'config' / 'locations.yaml')

    return LaunchDescription([
        rviz_arg,

        # A-1: 发布机器人模型描述（URDF）和静态 TF（fixed joints）
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            parameters=[{'robot_description': robot_description}],
            output='screen',
        ),

        # A-2: 发布合成激光扫描 /scan，并广播 odom->base_footprint TF
        Node(
            package='robot_sim',
            executable='fake_scan_node',
            name='fake_scan_node',
            parameters=[{
                'scan_frame_id': 'lidar_link',
                'scan_rate': 10.0,
                'num_readings': 360,
                'range_min': 0.1,
                'range_max': 10.0,
                'range_value': 5.0,
            }],
            output='screen',
        ),

        # A-3: RViz2（可选，默认关闭；用 rviz:=true 开启）
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config],
            output='screen',
            condition=IfCondition(LaunchConfiguration('rviz')),
        ),

        # B-1: 底盘驱动（stub 模式：发布 /odom 和 /estop，订阅 /cmd_vel）
        Node(
            package='robot_base',
            executable='base_driver_node',
            name='base_driver_node',
            parameters=[{'use_stub': True, 'cmd_timeout_ms': 200}],
            output='screen',
        ),

        # B-2: 安全节点（速度限幅）
        Node(
            package='robot_safety',
            executable='safety_node',
            name='safety_node',
            output='screen',
        ),

        # B-3: 导航服务节点（stub：根据 locations.yaml 返回坐标）
        Node(
            package='robot_nav',
            executable='nav_server_node',
            name='nav_server_node',
            parameters=[{
                'locations_file': locations_file,
                'handover_spot': '餐桌旁',
            }],
            output='screen',
        ),

        # C-1: 语音桥接节点（手动发 /voice/raw_text 模拟语音输入）
        Node(
            package='robot_voice',
            executable='voice_bridge_node',
            name='voice_bridge_node',
            output='screen',
        ),

        # C-2: NLU 节点（语音文字 → JSON 指令）
        Node(
            package='robot_nlu',
            executable='nlu_node',
            name='nlu_node',
            output='screen',
        ),

        # C-3: 身份识别节点
        Node(
            package='robot_identity',
            executable='identity_node',
            name='identity_node',
            output='screen',
        ),

        # C-4: 机械臂节点（sim_mode=True，无需硬件）
        Node(
            package='robot_manipulation',
            executable='manipulation_node',
            name='manipulation_node',
            parameters=[{'sim_mode': True}],
            output='screen',
        ),

        # C-5: 感知节点（stub 模式，无需 RealSense）
        Node(
            package='robot_perception',
            executable='perception_node',
            name='perception_node',
            output='screen',
        ),

        # C-6: 执行器节点（任务调度状态机）
        Node(
            package='robot_executor',
            executable='executor_node',
            name='executor_node',
            output='screen',
        ),
    ])
