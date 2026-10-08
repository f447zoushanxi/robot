#!/usr/bin/env python3
"""
executor_node.py

Executor node implementing a small FSM to drive high-level tasks such as
"deliver_water", "fold_clothes", or "collect_trash" in simulation.

Behavior:
- Provides services:
  - /executor/start_task (std_srvs/Trigger) -> starts a configured task (reads parameter 'task_name')
  - /executor/get_status  (std_srvs/Trigger) -> returns current state and last_detection
- Subscribes to /perception/detections_text for simple detection cues
- On detection, verifies identity via /robot_identity/verify_owner (Trigger) before proceeding

This is a scaffold/placeholder FSM: each action stage sleeps to simulate action time
and then progresses. In a real system each stage would call motion/planning/action servers.
"""
from __future__ import annotations

import threading
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
        self._task_thread: Optional[threading.Thread] = None
        self._task_cancel = threading.Event()

        # detection topic
        self.create_subscription(String, '/perception/detections_text', self._on_detection, 10)
        # start / status services
        self.create_service(Trigger, '/executor/start_task', self._handle_start_task)
        self.create_service(Trigger, '/executor/get_status', self._handle_get_status)

        self.get_logger().info('executor_node FSM started')

    # --------- service handlers -------------------------------------------------
    def _handle_get_status(self, request, response):
        response.success = True
        response.message = f'state={self.state} last_detection={self.last_detection}'
        return response

    def _handle_start_task(self, request, response):
        # If a task is already running, refuse
        if self._task_thread and self._task_thread.is_alive():
            response.success = False
            response.message = 'task already running'
            return response
        self._task_cancel.clear()
        self._task_thread = threading.Thread(target=self._run_task_fsm, daemon=True)
        self._task_thread.start()
        response.success = True
        response.message = 'task started'
        return response

    # --------- detection callback ------------------------------------------------
    def _on_detection(self, msg: String):
        self.get_logger().info(f'received detection: {msg.data}')
        self.last_detection = msg.data

    # --------- FSM ----------------------------------------------------------------
    def _run_task_fsm(self):
        # Example high-level FSM for a "deliver" or "collect" task.
        try:
            self._set_state('locating')
            # wait for a detection for a limited time
            found = self._wait_for_detection(timeout=5.0)
            if not found:
                self.get_logger().warn('no detection found, aborting')
                self._set_state('fallback')
                return

            # verify identity as a gating step
            self._set_state('verifying_identity')
            verified = self._verify_identity(timeout=2.0)
            if not verified:
                self.get_logger().warn('identity not verified, aborting')
                self._set_state('fallback')
                return

            self._set_state('approaching')
            time.sleep(1.0)  # simulate approach
            if self._task_cancel.is_set():
                self._set_state('cancelled')
                return

            self._set_state('grasping')
            time.sleep(0.8)  # simulate grasp
            self._set_state('transporting')
            time.sleep(1.2)  # simulate transport
            self._set_state('placing')
            time.sleep(0.6)  # simulate place
            self._set_state('verifying')
            time.sleep(0.4)

            self._set_state('done')
            return
        except Exception as e:
            self.get_logger().error(f'FSM error: {e}')
            self._set_state('error')

    def _wait_for_detection(self, timeout: float) -> bool:
        waited = 0.0
        interval = 0.1
        while waited < timeout:
            if self.last_detection is not None:
                return True
            time.sleep(interval)
            waited += interval
        return False

    def _verify_identity(self, timeout: float) -> bool:
        try:
            client = self.create_client(Trigger, '/robot_identity/verify_owner')
            if not client.wait_for_service(timeout_sec=timeout):
                return False
            req = Trigger.Request()
            future = client.call_async(req)
            rclpy.spin_until_future_complete(self, future, timeout_sec=timeout)
            if future.done() and future.result() is not None:
                return future.result().success
            return False
        except Exception:
            return False

    def _set_state(self, new_state: str) -> None:
        self.state = new_state
        self.get_logger().info(f'executor state -> {new_state}')


def main(args=None) -> int:
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
