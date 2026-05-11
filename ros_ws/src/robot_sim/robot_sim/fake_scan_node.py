# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 模块说明：robot_sim — 假激光扫描节点（fake_scan_node.py）
# =============================================================================
# 这个节点用于纯软件仿真，无需任何硬件。它的职责：
#
#   1. 发布 /scan（sensor_msgs/LaserScan）：合成的 360 度激光扫描数据，
#      所有射线距离固定，足以让 RViz 渲染激光点云。
#   2. 广播 TF odom -> base_footprint：让机器人在 odom 坐标系中有固定位置，
#      robot_state_publisher 在此基础上发布 base_footprint -> base_link 等静态变换。
#
# 参数（可在 launch 文件中覆盖）：
#   - scan_frame_id  (str,   默认 'lidar_link') ：扫描数据的坐标系
#   - scan_rate      (float, 默认 10.0)         ：发布频率（Hz）
#   - num_readings   (int,   默认 360)          ：每圈采样点数
#   - range_min      (float, 默认 0.1)          ：最小有效距离（m）
#   - range_max      (float, 默认 10.0)         ：最大有效距离（m）
#   - range_value    (float, 默认 5.0)          ：所有射线的固定距离（m）
#
# 运行方式（已安装 robot_sim 包后）：
#   ros2 run robot_sim fake_scan_node
# =============================================================================

from __future__ import annotations

import math

import rclpy
from geometry_msgs.msg import TransformStamped
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
import tf2_ros


class FakeScanNode(Node):
    """纯软件激光扫描仿真节点。

    发布合成的 LaserScan 消息，并广播 odom->base_footprint TF，
    使机器人在 RViz 中固定在 odom 原点。
    """

    def __init__(self) -> None:
        super().__init__('fake_scan_node')

        # --- 参数声明 ---
        self.declare_parameter('scan_frame_id', 'lidar_link')
        self.declare_parameter('scan_rate', 10.0)
        self.declare_parameter('num_readings', 360)
        self.declare_parameter('range_min', 0.1)
        self.declare_parameter('range_max', 10.0)
        self.declare_parameter('range_value', 5.0)

        self._frame_id = self.get_parameter('scan_frame_id').value
        scan_rate = float(self.get_parameter('scan_rate').value)
        self._num_readings = int(self.get_parameter('num_readings').value)
        self._range_min = float(self.get_parameter('range_min').value)
        self._range_max = float(self.get_parameter('range_max').value)
        self._range_value = float(self.get_parameter('range_value').value)

        # --- 发布者 ---
        self._scan_pub = self.create_publisher(LaserScan, '/scan', 10)

        # --- TF 广播器（odom -> base_footprint）---
        self._tf_broadcaster = tf2_ros.TransformBroadcaster(self)

        # --- 定时器 ---
        period = 1.0 / scan_rate
        self.create_timer(period, self._on_timer)

        self.get_logger().info(
            'fake_scan_node started  frame_id=%s  rate=%.1f Hz  readings=%d' % (
                self._frame_id, scan_rate, self._num_readings)
        )

    def _on_timer(self) -> None:
        """定时回调：每次发布一帧扫描数据并广播 TF。"""
        now = self.get_clock().now()

        # --- 发布合成 LaserScan ---
        scan = LaserScan()
        scan.header.stamp = now.to_msg()
        scan.header.frame_id = self._frame_id
        scan.angle_min = -math.pi
        scan.angle_max = math.pi
        scan.angle_increment = 2.0 * math.pi / self._num_readings
        scan.time_increment = 0.0
        scan.scan_time = 1.0 / 10.0
        scan.range_min = self._range_min
        scan.range_max = self._range_max
        scan.ranges = [self._range_value] * self._num_readings
        scan.intensities = []
        self._scan_pub.publish(scan)

        # --- 广播 TF：odom -> base_footprint（机器人停在原点不动）---
        t = TransformStamped()
        t.header.stamp = now.to_msg()
        t.header.frame_id = 'odom'
        t.child_frame_id = 'base_footprint'
        t.transform.translation.x = 0.0
        t.transform.translation.y = 0.0
        t.transform.translation.z = 0.0
        t.transform.rotation.w = 1.0
        self._tf_broadcaster.sendTransform(t)


def main(args=None) -> int:
    """节点入口函数（由 ros2 run 或 launch 文件调用）。"""
    rclpy.init(args=args)
    node = FakeScanNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        try:
            node.destroy_node()
        except Exception:
            pass
        try:
            if rclpy.ok():
                rclpy.shutdown()
        except Exception:
            pass
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
