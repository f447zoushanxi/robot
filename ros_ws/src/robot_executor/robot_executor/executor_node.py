#!/usr/bin/env python3
"""
Simple executor node for integration tests.
- Provides /executor/get_status (std_srvs/srv/Trigger)
- Subscribes to /perception/detections (DetectionArray topic name in future)
- Logs received detection and exposes a trivial state machine for tests
"""
from __future__ import annotations

import time
from typing import Optional

try:
    import rclpy
    from rclpy.node import Node
    from std_srvs.srv import Trigger
    from std_msgs.msg import String
except Exception:  # pragma: no cover
    rclpy = None
    Node = object


class ExecutorNode(Node):
    def __init__(self):
        super().__init__('executor_node')
        self.state = 'idle'
        self.last_detection: Optional[str] = None
        # subscribe to a texty detection topic to keep code simple for now
        self.create_subscription(String, '/perception/detections_text', self._on_detection, 10)
        self.create_service(Trigger, '/executor/get_status', self._handle_get_status)
        self.get_logger().info('executor_node started')

    def _on_detection(self, msg: String):
        self.get_logger().info(f'received detection: {msg.data}')
        self.last_detection = msg.data
        # simple state transition
        self.state = 'received_detection'

    def _handle_get_status(self, request, response):
        response.success = True
        response.message = f'state={self.state} last_detection={self.last_detection}'
        return response


def main(args=None):
    if rclpy is None:
        print('rclpy not available; run in ROS2 environment')
        return 0
    rclpy.init(args=args)
    node = ExecutorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        try:
            node.destroy_node()
        except Exception:
            pass
        if rclpy.ok():
            rclpy.shutdown()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
