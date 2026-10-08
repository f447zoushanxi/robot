#!/usr/bin/env python3
"""
launch_test_executor_flow.py

A launch_testing skeleton that starts the simulated bringup and executor/identity
nodes, triggers a perception detection (via topic publish), and asserts the
executor reaches the 'done' state within a timeout.

Note: This test is a scaffold and may need adaptation to your local bringup.
"""

import os
import time

import launch
from launch import LaunchDescription
from launch.actions import ExecuteProcess
import launch_testing

import pytest


def generate_test_description():
    ld = LaunchDescription()
    # Launch the bringup in dev_sim mode; assumes robot_bringup/dev_sim.launch.py exists
    ld.add_action(ExecuteProcess(cmd=['ros2', 'launch', 'robot_bringup', 'dev_sim.launch.py', 'rviz:=false'], cwd=os.getcwd()))
    return ld, {'bringup': None}


def test_executor_reaches_done():
    # This test is intentionally simple: it waits and then publishes a fake detection
    # to /perception/detections_text and polls /executor/get_status until 'done'.
    import rclpy
    from rclpy.node import Node
    from std_msgs.msg import String
    from std_srvs.srv import Trigger

    rclpy.init()
    node = Node('test_pub')
    pub = node.create_publisher(String, '/perception/detections_text', 10)

    # give bringup time
    time.sleep(6)

    # start task
    import subprocess
    subprocess.run(['ros2', 'service', 'call', '/executor/start_task', 'std_srvs/srv/Trigger', '{}'])

    # publish a detection
    pub.publish(String(data='yolov8:bottle:0.95'))

    # poll executor status
    client = node.create_client(Trigger, '/executor/get_status')
    start = time.time()
    timeout = 20.0
    reached = False
    while time.time() - start < timeout:
        if client.wait_for_service(timeout_sec=1.0):
            future = client.call_async(Trigger.Request())
            rclpy.spin_until_future_complete(node, future, timeout_sec=1.0)
            if future.done() and future.result() is not None:
                s = future.result().message
                if 'done' in s:
                    reached = True
                    break
        time.sleep(0.5)

    node.destroy_node()
    rclpy.shutdown()
    assert reached, 'executor did not reach done state in time'
