# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 模块说明：robot_perception — 感知节点（perception_node.py）
# =============================================================================
# 这个节点负责"让机器人看懂世界"——通过摄像头（RealSense）识别物体和人。
#
# 两个核心能力（均为 ROS2 服务接口）：
#   1) detect_bottle（检测水瓶）：
#      - 订阅 RealSense 的彩色图（/camera/color/image_raw）
#      - 用 ONNX 推理模型（AI 目标检测）找到水瓶在图像中的像素位置
#      - 结合深度图（/camera/aligned_depth_to_color/image_raw）计算水瓶的 3D 坐标
#      - 通过相机内参（K 矩阵）把像素坐标反投影成真实世界坐标
#
#   2) find_person（寻找人）：
#      - 在图像中检测人体或人脸
#      - 返回人的 3D 位置和身份（当前为 stub，返回固定值）
#
# 当前状态（stub/占位）：
#   - AI 推理部分用固定值代替（像素坐标 320,240，深度 0.72m）
#   - 真实项目：用 ONNX Runtime 加载 YOLOv8 或类似模型进行推理
#
# 服务（Services）：
#   - /perception/detect_bottle [robot_msgs/DetectObject]  检测水瓶
#   - /perception/find_person   [robot_msgs/FindPerson]    寻找人
#
# 订阅话题（Subscriptions）：
#   - /camera/color/image_raw                  彩色图像
#   - /camera/aligned_depth_to_color/image_raw 对齐深度图
#   - /camera/color/camera_info                相机内参（焦距等）
# =============================================================================

from __future__ import annotations

import statistics
from typing import Optional, Sequence, Tuple

# 尝试导入 ROS2 模块（在没有 ROS2 环境时降级为 None，避免导入错误）
try:
    import rclpy
    from geometry_msgs.msg import Point
    from rclpy.node import Node
    from sensor_msgs.msg import CameraInfo, Image
    from robot_msgs.srv import DetectObject, FindPerson
except ImportError:  # pragma: no cover
    # 没有 ROS2 环境时（例如只跑单元测试），用 None/object 占位
    rclpy = None
    Node = object
    Point = object
    CameraInfo = object
    Image = object
    DetectObject = object
    FindPerson = object


class PerceptionNode(Node):
    """感知模板节点：
    1) 订阅 RealSense 彩色图、对齐深度图、相机内参。
    2) 提供 detect_bottle/find_person 服务。
    3) 预留 ONNX Runtime 推理入口（当前为 stub）。

    注意：本节点要能在 launch_testing 的测试环境中"干净退出"，
    所以 shutdown 逻辑需要容错（重复 shutdown 不应导致进程崩溃）。
    """

    def __init__(self) -> None:
        super().__init__('perception_node')

        # 保存最新接收到的图像帧（供服务处理函数使用）
        self.color_msg: Optional[Image] = None    # 彩色图（RGB）
        self.depth_msg: Optional[Image] = None    # 深度图（每像素距离）
        self.camera_info: Optional[CameraInfo] = None  # 相机内参（焦距 fx/fy，光心 cx/cy）

        # 订阅 RealSense 发布的三个话题（无硬件时这些话题没有数据，节点仍正常启动）
        self.create_subscription(Image, '/camera/color/image_raw', self._on_color, 10)
        self.create_subscription(
            Image,
            '/camera/aligned_depth_to_color/image_raw',
            self._on_depth,
            10,
        )
        self.create_subscription(CameraInfo, '/camera/color/camera_info', self._on_info, 10)

        # 注册两个感知服务（executor_node 会调用这些服务）
        self.create_service(DetectObject, '/perception/detect_bottle', self._handle_detect_bottle)
        self.create_service(FindPerson, '/perception/find_person', self._handle_find_person)

        self.get_logger().info('robot_perception started (stub ONNX + depth projection pipeline).')

    # --- 话题回调：保存最新图像帧 ---

    def _on_color(self, msg: Image) -> None:
        """收到彩色图时保存，供检测服务使用"""
        self.color_msg = msg

    def _on_depth(self, msg: Image) -> None:
        """收到深度图时保存，供 3D 位置计算使用"""
        self.depth_msg = msg

    def _on_info(self, msg: CameraInfo) -> None:
        """收到相机内参时保存，供像素反投影使用"""
        self.camera_info = msg

    def _handle_detect_bottle(self, request: DetectObject.Request, response: DetectObject.Response):
        """处理"检测水瓶"服务请求

        真实流程：
          1. 用 ONNX 模型在彩色图上推理，找到水瓶的像素坐标 (u, v)
          2. 在深度图的 (u, v) 邻域取中值深度，去掉噪声
          3. 用相机内参把 (u, v, depth) 反投影成相机坐标系 3D 点
          4. 用 tf2 把相机坐标转换到 base_link 坐标系
        """
        # TODO: 用 ONNX Runtime 推理结果替换该占位中心点 (u, v)。
        # 当前 stub：假设水瓶总在图像正中心（640x480 图像的中心）
        u, v = 320, 240

        # TODO: 从 self.depth_msg 的 (u,v) 邻域提取深度窗口并取中值。
        # 当前 stub：直接给几个固定深度值，取中值
        depth_m = self._median_depth_stub([0.72, 0.73, 0.70, 0.71, 0.74])

        # 像素反投影到相机坐标系，再 tf2 变换到 base_link（此处先给结构）。
        x, y, z = self._back_project_pixel_to_3d(u, v, depth_m)

        response.found = True
        response.position = Point(x=float(x), y=float(y), z=float(z))
        response.confidence = 0.5  # 置信度（stub 给 0.5，真实推理会给 0~1 的值）
        response.frame_id = 'base_link'
        response.message = f'stub detect {request.object_name} timeout={request.timeout_sec}'
        return response

    def _handle_find_person(self, request: FindPerson.Request, response: FindPerson.Response):
        """处理"寻找人"服务请求

        真实流程：
          1. 用人体检测/人脸识别模型在彩色图上找人
          2. 用深度图计算人的 3D 位置
          3. 如果 hint_name 不为空，尝试匹配特定人的身份
        """
        # stub：假装找到了人，位置在机器人正前方 1 米处
        response.found = True
        response.position = Point(x=1.0, y=0.0, z=0.0)  # 相对 base_link，正前方 1m
        response.confidence = 0.4
        # 如果调用方提供了提示名字，就用那个名字；否则报告 unknown
        response.identity = request.hint_name if request.hint_name else 'unknown'
        response.message = 'stub find_person result'
        return response

    @staticmethod
    def _median_depth_stub(values: Sequence[float]) -> float:
        """从一组深度值中取中值（去噪：中值比均值更能抵抗噪声点）

        真实实现：从深度图矩阵中提取 (u-w, v-w) 到 (u+w, v+w) 的窗口，
        把有效深度值（非零、非 inf）收集后取中值。
        """
        return float(statistics.median(values))

    def _back_project_pixel_to_3d(
        self, u: int, v: int, depth_m: float
    ) -> Tuple[float, float, float]:
        """把图像像素坐标 (u, v) 和深度 depth_m 转换成相机坐标系 3D 点

        相机内参矩阵 K（从 CameraInfo 消息获取）：
          K = [fx,  0, cx, 0, fy, cy, 0, 0, 1]
          fx, fy：焦距（像素单位）
          cx, cy：光心（图像中心，像素单位）

        反投影公式：
          X = (u - cx) / fx * Z    (Z = depth_m)
          Y = (v - cy) / fy * Z
          Z = depth_m
        """
        # CameraInfo 的 K = [fx, 0, cx, 0, fy, cy, 0, 0, 1]
        # 反投影：X = (u-cx)/fx * Z, Y = (v-cy)/fy * Z, Z = depth
        # 默认值（没有相机内参时用的猜测值，640x480 普通摄像头）
        fx, fy, cx, cy = 600.0, 600.0, 320.0, 240.0
        if self.camera_info is not None and len(self.camera_info.k) >= 6:
            # 从实际相机内参读取（更准确）
            fx = self.camera_info.k[0]
            fy = self.camera_info.k[4]
            cx = self.camera_info.k[2]
            cy = self.camera_info.k[5]

        x = (u - cx) / fx * depth_m
        y = (v - cy) / fy * depth_m
        z = depth_m

        # 真实项目：在这里调用 tf2，把 camera_frame 点转换到 base_link。
        return x, y, z


def _safe_shutdown() -> None:
    """安全地关闭 rclpy。

    在 launch_testing 中，测试框架可能已经调用了 shutdown()。
    第二次 shutdown() 会抛出 RCLError，导致进程以非零退出码结束，
    从而使 bringup 测试失败。因此这里捕获所有异常，确保安全退出。
    """

    if rclpy is None:
        return

    try:
        if rclpy.ok():
            rclpy.shutdown()
    except Exception:
        # Never raise during shutdown path.
        pass


def main(args=None) -> int:
    """程序入口函数（由 console_scripts 或 ros2 run 调用）

    启动流程：
      1. 初始化 rclpy（ROS2 Python 库）
      2. 创建 PerceptionNode 节点
      3. 进入事件循环（spin），等待图像和服务请求
      4. 接收到 Ctrl+C 后退出并清理资源
    """
    if rclpy is None:
        print('rclpy is not available. Please source ROS 2 Humble environment first.')
        return 0

    rclpy.init(args=args)
    node = PerceptionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        # Ctrl+C 退出：正常结束，不打印报错
        pass
    finally:
        try:
            node.destroy_node()
        except Exception:
            pass
        _safe_shutdown()

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
