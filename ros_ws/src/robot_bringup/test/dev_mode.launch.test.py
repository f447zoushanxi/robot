# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 测试说明：robot_bringup — dev_mode 集成测试（dev_mode.launch.test.py）
# =============================================================================
# 这个文件是"集成测试"（Integration Test）——不是测试单个函数，
# 而是真正启动所有节点，验证整个系统能一起正常工作。
#
# 什么是集成测试？
#   想象你组装了一台自行车，单元测试是"测每个零件是否合格"，
#   集成测试是"把所有零件装好后，骑一圈看能不能正常行驶"。
#
# 这个测试做什么？
#   1. 启动 dev_mode.launch.py（所有核心节点）
#   2. 等待核心节点都出现在 ROS2 节点图中
#   3. 等待核心服务（感知/身份/机械臂）可用
#   4. 直接向 /voice/asr_text 发布语音文字（不依赖真实麦克风）：
#      - "请给我递水" -> NLU 输出 deliver_water
#      - "立刻停下"   -> NLU 输出 stop
#      - executor 在每条命令后都发布 /robot/state（证明执行器在运行）
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
from rclpy.node import Node
from robot_msgs.srv import DetectObject, EnrollOwner
from std_msgs.msg import String
from std_srvs.srv import Trigger


# @keep_alive：告诉 launch_testing 在测试运行期间保持 launch 进程不退出
@launch_testing.markers.keep_alive
def generate_test_description():
    """启动 dev_mode.launch.py 作为被测系统（DUT = Device Under Test）"""
    launch_file = os.path.join(
        get_package_share_directory('robot_bringup'),
        'launch',
        'dev_mode.launch.py',
    )
    # IncludeLaunchDescription：在当前 launch 中嵌套另一个 launch 文件
    dut = IncludeLaunchDescription(PythonLaunchDescriptionSource(launch_file))
    return launch.LaunchDescription([
        dut,
        launch_testing.actions.ReadyToTest(),  # 告知测试框架 launch 已就绪
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
        """测试类启动前执行一次：初始化 rclpy，创建测试节点和订阅/发布"""
        rclpy.init()
        # 创建一个辅助测试节点（用于订阅/发布，检查系统状态）
        cls.node = Node('dev_mode_launch_test_node')

        # 用于接收 NLU 解析结果（验证语音→NLU 是否工作）
        cls.received_nlu_msgs = []
        # 用于接收状态变化（验证 executor 是否被触发）
        cls.received_states = []

        # 订阅 NLU 输出话题
        cls.nlu_sub = cls.node.create_subscription(
            String, '/nlu/command_json', cls._on_nlu, 10)
        # 订阅机器人状态话题
        cls.state_sub = cls.node.create_subscription(
            String, '/robot/state', cls._on_state, 10)
        # 创建 ASR 输入发布者（测试直接发到 /voice/asr_text，最贴近 NLU 输入契约）
        cls.asr_pub = cls.node.create_publisher(String, '/voice/asr_text', 10)

        cls.node.get_logger().info('dev_mode launch test node started')

    @classmethod
    def tearDownClass(cls):
        """测试类结束后执行：清理 ROS2 资源"""
        try:
            cls.node.get_logger().info('dev_mode launch test node shutting down')
        except Exception:
            pass

        cls.node.destroy_node()
        rclpy.shutdown()

    @classmethod
    def _on_nlu(cls, msg):
        """收到 NLU 解析结果时保存"""
        cls.received_nlu_msgs.append(msg.data)

    @classmethod
    def _on_state(cls, msg):
        """收到机器人状态时追加到列表"""
        cls.received_states.append(msg.data)

    def _spin_until(self, condition, timeout_sec=20.0, debug_name: str = ''):
        """等待条件满足，超时返回 False

        参数 condition   ：无参 lambda，返回 True 时表示条件满足
        参数 timeout_sec ：最长等待秒数
        参数 debug_name  ：调试名称（每 2 秒打印一次节点状态，方便定位问题）
        """
        deadline = time.time() + timeout_sec
        last_log = 0.0
        while time.time() < deadline:
            # spin_once：处理一次消息队列（非阻塞）
            rclpy.spin_once(self.node, timeout_sec=0.1)

            now = time.time()
            # 每 2 秒打印一次当前可见节点列表（帮助调试）
            if debug_name and (now - last_log) > 2.0:
                names = self.node.get_node_names()
                self.node.get_logger().info(
                    f'[wait:{debug_name}] visible_nodes={len(names)} names={sorted(set(names))}')
                last_log = now

            if condition():
                return True
        return False

    def test_core_services_available(self):
        """测试：核心服务是否可用（感知/身份/机械臂）"""
        # 创建服务客户端（只用来检查服务是否存在，不实际调用）
        detect_client = self.node.create_client(DetectObject, '/perception/detect_bottle')
        enroll_client = self.node.create_client(EnrollOwner, '/identity/enroll_owner')
        pick_client = self.node.create_client(Trigger, '/manipulation/pick_bottle')

        # wait_for_service：等待服务节点启动并注册服务（最多 20 秒）
        self.assertTrue(detect_client.wait_for_service(timeout_sec=20.0))
        self.assertTrue(enroll_client.wait_for_service(timeout_sec=20.0))
        self.assertTrue(pick_client.wait_for_service(timeout_sec=20.0))

    def test_core_nodes_started(self):
        """测试：所有核心节点是否都已启动并出现在 ROS2 节点图中"""
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

        # 等待所有期望节点出现在节点图（最多 30 秒，CI 环境启动可能较慢）
        self.assertTrue(
            self._spin_until(
                lambda: expected.issubset(set(self.node.get_node_names())),
                timeout_sec=30.0,
                debug_name='core_nodes_started',
            ),
            msg='Timed out waiting for core nodes to appear in ROS graph',
        )

        # 打印缺失节点（如果有），便于快速定位问题
        names = set(self.node.get_node_names())
        missing = sorted(expected - names)
        self.node.get_logger().info(f'core_nodes_started check: missing={missing} all={sorted(names)}')
        self.assertTrue(expected.issubset(names), msg=f'Missing nodes: {missing}')

    def _assert_asr_triggers_intent_and_state_update(self, text, expected_intent):
        """发布一条 ASR 文本并断言 NLU/Executor 都有响应。

        为什么要带 timeout + retries？
        - CI 机器负载波动较大，节点发现和消息传递可能比本地慢。
        - 通过超时等待和短重发，可以减少偶发 flaky 失败。
        """
        nlu_before = len(self.received_nlu_msgs)
        state_before = len(self.received_states)

        msg = String()
        msg.data = text

        # 先等待 /voice/asr_text 有订阅者（nlu_node 订阅了它）
        self.assertTrue(
            self._spin_until(
                lambda: self.asr_pub.get_subscription_count() > 0,
                timeout_sec=20.0,
                debug_name='asr_subscribers',
            )
        )

        # 发布多次（网络可能丢包，发 5 次确保至少到达一次）
        for i in range(5):
            self.node.get_logger().info(f'publishing voice/asr_text attempt={i + 1} text={msg.data!r}')
            self.asr_pub.publish(msg)
            rclpy.spin_once(self.node, timeout_sec=0.1)

        # 等待 NLU 解析出期望 intent
        self.assertTrue(
            self._spin_until(
                lambda: any(expected_intent in x for x in self.received_nlu_msgs[nlu_before:]),
                timeout_sec=20.0,
                debug_name=f'wait_nlu_{expected_intent}',
            )
        )
        self.node.get_logger().info(
            f'received nlu/command_json after publish={self.received_nlu_msgs[nlu_before:]!r}')

        # 要求：命令发出后，/robot/state 在超时内有新消息，证明 executor 仍在响应
        self.assertTrue(
            self._spin_until(
                lambda: len(self.received_states) > state_before,
                timeout_sec=20.0,
                debug_name=f'wait_state_after_{expected_intent}',
            )
        )

    def test_asr_to_nlu_deliver_water_and_executor_state(self):
        """测试文本链路：请给我递水 -> intent=deliver_water。"""
        self._assert_asr_triggers_intent_and_state_update('请给我递水', 'deliver_water')

    def test_asr_to_nlu_stop_and_executor_state(self):
        """测试文本链路：立刻停下 -> intent=stop。"""
        self._assert_asr_triggers_intent_and_state_update('立刻停下', 'stop')
