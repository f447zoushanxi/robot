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
from rclpy.node import Node
from robot_msgs.srv import DetectObject, EnrollOwner
from std_msgs.msg import String
from std_srvs.srv import Trigger


@launch_testing.markers.keep_alive
def generate_test_description():
    launch_file = os.path.join(
        get_package_share_directory('robot_bringup'),
        'launch',
        'dev_mode.launch.py',
    )
    dut = IncludeLaunchDescription(PythonLaunchDescriptionSource(launch_file))
    return launch.LaunchDescription([
        dut,
        launch_testing.actions.ReadyToTest(),
    ]), {}


class TestDevModeBringup(unittest.TestCase):
    """Bringup integration test for dev_mode.launch.py.

    Why so much logging?
    - In CI we cannot inspect a running robot.
    - When a node is missing, we want the test output to immediately show:
      * currently visible node list
      * which nodes are missing
      * how many nodes are visible over time

    This makes failures actionable without re-running locally.
    """

    @classmethod
    def setUpClass(cls):
        rclpy.init()
        cls.node = Node('dev_mode_launch_test_node')
        cls.received_nlu = None
        cls.received_states = []
        cls.nlu_sub = cls.node.create_subscription(
            String, '/nlu/command_json', cls._on_nlu, 10)
        cls.state_sub = cls.node.create_subscription(
            String, '/robot/state', cls._on_state, 10)
        cls.voice_pub = cls.node.create_publisher(String, '/voice/raw_text', 10)

        cls.node.get_logger().info('dev_mode launch test node started')

    @classmethod
    def tearDownClass(cls):
        try:
            cls.node.get_logger().info('dev_mode launch test node shutting down')
        except Exception:
            pass

        cls.node.destroy_node()
        rclpy.shutdown()

    @classmethod
    def _on_nlu(cls, msg):
        cls.received_nlu = msg.data

    @classmethod
    def _on_state(cls, msg):
        cls.received_states.append(msg.data)

    def _spin_until(self, condition, timeout_sec=20.0, debug_name: str = ''):
        deadline = time.time() + timeout_sec
        last_log = 0.0
        while time.time() < deadline:
            rclpy.spin_once(self.node, timeout_sec=0.1)

            now = time.time()
            if debug_name and (now - last_log) > 2.0:
                names = self.node.get_node_names()
                self.node.get_logger().info(
                    f'[wait:{debug_name}] visible_nodes={len(names)} names={sorted(set(names))}')
                last_log = now

            if condition():
                return True
        return False

    def test_core_services_available(self):
        detect_client = self.node.create_client(DetectObject, '/perception/detect_bottle')
        enroll_client = self.node.create_client(EnrollOwner, '/identity/enroll_owner')
        pick_client = self.node.create_client(Trigger, '/manipulation/pick_bottle')

        self.assertTrue(detect_client.wait_for_service(timeout_sec=20.0))
        self.assertTrue(enroll_client.wait_for_service(timeout_sec=20.0))
        self.assertTrue(pick_client.wait_for_service(timeout_sec=20.0))

    def test_core_nodes_started(self):
        # Node graph discovery can be slow in containers/CI. We wait until the expected
        # nodes are visible, and print the missing subset on failure for quick diagnosis.
        expected = {
            'base_driver_node',
            'safety_node',
            'voice_bridge_node',
            'nlu_node',
            'identity_node',
            'manipulation_node',
            'perception_node',
            'executor_node',
        }

        self.assertTrue(
            self._spin_until(
                lambda: expected.issubset(set(self.node.get_node_names())),
                timeout_sec=30.0,
                debug_name='core_nodes_started',
            ),
            msg='Timed out waiting for core nodes to appear in ROS graph',
        )

        names = set(self.node.get_node_names())
        missing = sorted(expected - names)
        self.node.get_logger().info(f'core_nodes_started check: missing={missing} all={sorted(names)}')
        self.assertTrue(expected.issubset(names), msg=f'Missing nodes: {missing}')

    def test_voice_to_nlu_and_executor_progress(self):
        msg = String()
        msg.data = '请给我递水'
        self.assertTrue(
            self._spin_until(
                lambda: self.voice_pub.get_subscription_count() > 0,
                timeout_sec=20.0,
                debug_name='voice_subscribers',
            )
        )

        for i in range(5):
            self.node.get_logger().info(f'publishing voice/raw_text attempt={i + 1} text={msg.data!r}')
            self.voice_pub.publish(msg)
            rclpy.spin_once(self.node, timeout_sec=0.1)

        self.assertTrue(
            self._spin_until(
                lambda: self.received_nlu is not None,
                timeout_sec=20.0,
                debug_name='wait_nlu',
            )
        )
        self.node.get_logger().info(f'received nlu/command_json={self.received_nlu!r}')
        self.assertIn('deliver_water', self.received_nlu)

        self.assertTrue(
            self._spin_until(
                lambda: any(state != 'IDLE' for state in self.received_states),
                timeout_sec=20.0,
                debug_name='wait_state_change',
            )
        )
