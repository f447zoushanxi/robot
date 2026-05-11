# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 测试说明：robot_bringup — dev_sim 集成测试（dev_sim.launch.test.py）
# =============================================================================
# 这个测试验证 dev_sim.launch.py 能成功启动，并且关键节点和话题都可用。
#
# 测试内容：
#   1. robot_state_publisher 节点启动（A 目标：机器人模型/TF 树）
#   2. fake_scan_node 节点启动（激光扫描仿真）
#   3. /scan 话题收到数据（证明 fake_scan_node 正常工作）
#   4. /odom 话题收到数据（证明 base_driver_node 正常工作）
#
# 运行方式：
#   cd ros_ws && colcon test --packages-select robot_bringup
#   colcon test-result --verbose
# =============================================================================

import os
import time
import unittest

import launch
import launch_testing
import launch_testing.actions
import launch_testing.markers
import rclpy
from ament_index_python.packages import get_package_share_directory
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from nav_msgs.msg import Odometry
from rclpy.node import Node
from sensor_msgs.msg import LaserScan


@launch_testing.markers.keep_alive
def generate_test_description():
    """启动 dev_sim.launch.py 作为被测系统。"""
    launch_file = os.path.join(
        get_package_share_directory('robot_bringup'),
        'launch',
        'dev_sim.launch.py',
    )
    dut = IncludeLaunchDescription(PythonLaunchDescriptionSource(launch_file))
    return launch.LaunchDescription([
        dut,
        launch_testing.actions.ReadyToTest(),
    ]), {}


class TestDevSimBringup(unittest.TestCase):
    """dev_sim.launch.py 集成测试：验证仿真节点和核心话题均可用。"""

    @classmethod
    def setUpClass(cls):
        rclpy.init()
        cls.node = Node('dev_sim_launch_test_node')

        # 用于接收 /scan 消息
        cls.received_scan = None
        # 用于接收 /odom 消息
        cls.received_odom = None

        cls.scan_sub = cls.node.create_subscription(
            LaserScan, '/scan', cls._on_scan, 10)
        cls.odom_sub = cls.node.create_subscription(
            Odometry, '/odom', cls._on_odom, 10)

        cls.node.get_logger().info('dev_sim launch test node started')

    @classmethod
    def tearDownClass(cls):
        try:
            cls.node.get_logger().info('dev_sim launch test node shutting down')
        except Exception:
            pass
        cls.node.destroy_node()
        rclpy.shutdown()

    @classmethod
    def _on_scan(cls, msg):
        cls.received_scan = msg

    @classmethod
    def _on_odom(cls, msg):
        cls.received_odom = msg

    def _spin_until(self, condition, timeout_sec=30.0, debug_name=''):
        """等待条件满足，每隔 2 秒打印一次调试信息。"""
        deadline = time.time() + timeout_sec
        last_log = 0.0
        while time.time() < deadline:
            rclpy.spin_once(self.node, timeout_sec=0.1)
            now = time.time()
            if debug_name and (now - last_log) > 2.0:
                names = self.node.get_node_names()
                self.node.get_logger().info(
                    f'[wait:{debug_name}] visible_nodes={len(names)}'
                    f' names={sorted(set(names))}'
                )
                last_log = now
            if condition():
                return True
        return False

    def test_sim_nodes_started(self):
        """测试：仿真关键节点是否都已启动。"""
        expected = {
            'robot_state_publisher',
            'fake_scan_node',
            'base_driver_node',
        }
        self.assertTrue(
            self._spin_until(
                lambda: expected.issubset(set(self.node.get_node_names())),
                timeout_sec=30.0,
                debug_name='sim_nodes_started',
            ),
            msg='Timed out waiting for simulation nodes to appear in ROS graph',
        )
        names = set(self.node.get_node_names())
        missing = sorted(expected - names)
        self.node.get_logger().info(
            f'sim_nodes_started check: missing={missing} all={sorted(names)}'
        )
        self.assertTrue(expected.issubset(names), msg=f'Missing nodes: {missing}')

    def test_scan_topic_receives_data(self):
        """测试：/scan 话题能收到 fake_scan_node 发布的激光数据。"""
        self.assertTrue(
            self._spin_until(
                lambda: self.received_scan is not None,
                timeout_sec=30.0,
                debug_name='wait_scan',
            ),
            msg='Timed out waiting for /scan messages',
        )
        self.assertIsNotNone(self.received_scan)
        self.node.get_logger().info(
            f'received /scan  frame_id={self.received_scan.header.frame_id}'
            f'  num_ranges={len(self.received_scan.ranges)}'
        )
        self.assertEqual(self.received_scan.header.frame_id, 'lidar_link')
        self.assertGreater(len(self.received_scan.ranges), 0)

    def test_odom_topic_receives_data(self):
        """测试：/odom 话题能收到 base_driver_node 发布的里程计数据。"""
        self.assertTrue(
            self._spin_until(
                lambda: self.received_odom is not None,
                timeout_sec=30.0,
                debug_name='wait_odom',
            ),
            msg='Timed out waiting for /odom messages',
        )
        self.assertIsNotNone(self.received_odom)
        self.node.get_logger().info(
            f'received /odom  frame_id={self.received_odom.header.frame_id}'
            f'  child_frame_id={self.received_odom.child_frame_id}'
        )
        self.assertEqual(self.received_odom.header.frame_id, 'odom')
