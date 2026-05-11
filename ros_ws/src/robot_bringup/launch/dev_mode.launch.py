# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 模块说明：robot_bringup — 开发模式启动文件（dev_mode.launch.py）
# =============================================================================
# 这个 launch 文件一键启动所有核心 ROS2 节点，适合"纯电脑开发"场景。
#
# 什么是 launch 文件？
#   就像"一键开机脚本"——一条命令启动多个节点，不用一个一个手动运行。
#   运行方式：
#     cd ros_ws && source install/setup.bash
#     ros2 launch robot_bringup dev_mode.launch.py
#
# 启动的节点列表（以及默认参数）：
#   1. base_driver_node   (robot_base)     ：底盘驱动（use_stub=True，不需要硬件）
#   2. safety_node        (robot_safety)   ：速度安全守门员
#   3. voice_bridge_node  (robot_voice)    ：语音桥接（手动发 /voice/raw_text 模拟语音）
#   4. nlu_node           (robot_nlu)      ：自然语言理解（语音文字 → JSON 指令）
#   5. identity_node      (robot_identity) ：身份识别（owner/guest/unknown）
#   6. manipulation_node  (robot_manipulation)：机械臂操作（sim_mode=True，不需要硬件）
#   7. perception_node    (robot_perception)  ：感知（stub 模式，不需要摄像头）
#   8. executor_node      (robot_executor) ：任务执行器（状态机大脑）
#
# 测试语音输入（另开一个终端）：
#   ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
#
# 观察状态变化：
#   ros2 topic echo /robot/state
# =============================================================================

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    """生成 launch 描述——告诉 ROS2 启动哪些节点和参数"""
    return LaunchDescription([
        # 底盘驱动节点：use_stub=True 表示不需要真实底盘硬件
        # cmd_timeout_ms=200：200ms 没收到速度指令就自动刹车
        Node(
            package='robot_base',
            executable='base_driver_node',
            name='base_driver_node',
            parameters=[{'use_stub': True, 'cmd_timeout_ms': 200}],
            output='screen',
        ),
        # 安全节点：对速度限幅，处理急停信号
        Node(
            package='robot_safety',
            executable='safety_node',
            name='safety_node',
            output='screen',
        ),
        # 语音桥接节点：转发外部语音输入到 /voice/asr_text
        Node(
            package='robot_voice',
            executable='voice_bridge_node',
            name='voice_bridge_node',
            output='screen',
        ),
        # NLU 节点：把语音文字解析成结构化 JSON 指令
        Node(
            package='robot_nlu',
            executable='nlu_node',
            name='nlu_node',
            output='screen',
        ),
        # 身份识别节点：判断当前用户是 owner/guest/unknown
        Node(
            package='robot_identity',
            executable='identity_node',
            name='identity_node',
            output='screen',
        ),
        # 机械臂节点：sim_mode=True 表示不需要真实机械臂，直接返回成功
        Node(
            package='robot_manipulation',
            executable='manipulation_node',
            name='manipulation_node',
            parameters=[{'sim_mode': True}],
            output='screen',
        ),
        # 感知节点：stub 模式，不需要 RealSense 摄像头
        Node(
            package='robot_perception',
            executable='perception_node',
            name='perception_node',
            output='screen',
        ),
        # 执行器节点：状态机大脑，协调所有其他节点完成任务
        Node(
            package='robot_executor',
            executable='executor_node',
            name='executor_node',
            output='screen',
        ),
    ])
