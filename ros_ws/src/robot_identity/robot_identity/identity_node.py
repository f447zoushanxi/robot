#!/usr/bin/env python3
"""
robot_identity/identity_node.py

A minimal identity verification node used by executor in integration tests.
Provides a Trigger service /robot_identity/verify_owner that returns success=True
for the stub. In future this can be extended to perform face/voice matching.
"""
from __future__ import annotations

try:
    import rclpy
    from rclpy.node import Node
    from std_srvs.srv import Trigger
except Exception:
    rclpy = None
    Node = object


class IdentityNode(Node):
    def __init__(self):
        super().__init__('robot_identity')
        self.create_service(Trigger, '/robot_identity/verify_owner', self._handle_verify)
        self.get_logger().info('robot_identity stub started')

    def _handle_verify(self, request, response):
        # stub: always verify owner successfully
        response.success = True
        response.message = 'owner_verified_stub'
        return response


def main(args=None):
    if rclpy is None:
        print('rclpy not available; run in ROS2 environment')
        return 0
    rclpy.init(args=args)
    node = IdentityNode()
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
