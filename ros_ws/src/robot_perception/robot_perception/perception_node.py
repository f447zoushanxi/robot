from __future__ import annotations

import statistics
from typing import Optional, Sequence, Tuple

try:
    import rclpy
    from geometry_msgs.msg import Point
    from rclpy.node import Node
    from sensor_msgs.msg import CameraInfo, Image
    from robot_msgs.srv import DetectObject, FindPerson
except ImportError:  # pragma: no cover
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
    """

    def __init__(self) -> None:
        super().__init__('perception_node')

        self.color_msg: Optional[Image] = None
        self.depth_msg: Optional[Image] = None
        self.camera_info: Optional[CameraInfo] = None

        self.create_subscription(Image, '/camera/color/image_raw', self._on_color, 10)
        self.create_subscription(
            Image,
            '/camera/aligned_depth_to_color/image_raw',
            self._on_depth,
            10,
        )
        self.create_subscription(CameraInfo, '/camera/color/camera_info', self._on_info, 10)

        self.create_service(DetectObject, '/perception/detect_bottle', self._handle_detect_bottle)
        self.create_service(FindPerson, '/perception/find_person', self._handle_find_person)

        self.get_logger().info('robot_perception started (stub ONNX + depth projection pipeline).')

    def _on_color(self, msg: Image) -> None:
        self.color_msg = msg

    def _on_depth(self, msg: Image) -> None:
        self.depth_msg = msg

    def _on_info(self, msg: CameraInfo) -> None:
        self.camera_info = msg

    def _handle_detect_bottle(self, request: DetectObject.Request, response: DetectObject.Response):
        # TODO: 用 ONNX Runtime 推理结果替换该占位中心点 (u, v)。
        # 1) ONNX 检测占位：真实项目应返回像素框中心 (u, v)。
        u, v = 320, 240

        # TODO: 从 self.depth_msg 的 (u,v) 邻域提取深度窗口并取中值，替换示例数组。
        # 2) 深度中值滤波（模板）：对 (u,v) 周边窗口取中值，抑制噪声。
        depth_m = self._median_depth_stub([0.72, 0.73, 0.70, 0.71, 0.74])

        # 3) 像素反投影到相机坐标系，再 tf2 变换到 base_link（此处先给结构）。
        x, y, z = self._back_project_pixel_to_3d(u, v, depth_m)

        response.found = True
        response.position = Point(x=float(x), y=float(y), z=float(z))
        response.confidence = 0.5
        response.frame_id = 'base_link'
        response.message = f'stub detect {request.object_name} timeout={request.timeout_sec}'
        return response

    def _handle_find_person(self, request: FindPerson.Request, response: FindPerson.Response):
        response.found = True
        response.position = Point(x=1.0, y=0.0, z=0.0)
        response.confidence = 0.4
        response.identity = request.hint_name if request.hint_name else 'unknown'
        response.message = 'stub find_person result'
        return response

    @staticmethod
    def _median_depth_stub(values: Sequence[float]) -> float:
        return float(statistics.median(values))

    def _back_project_pixel_to_3d(self, u: int, v: int, depth_m: float) -> Tuple[float, float, float]:
        # CameraInfo 的 K = [fx, 0, cx, 0, fy, cy, 0, 0, 1]
        # 反投影：X = (u-cx)/fx * Z, Y = (v-cy)/fy * Z, Z = depth
        fx, fy, cx, cy = 600.0, 600.0, 320.0, 240.0
        if self.camera_info is not None and len(self.camera_info.k) >= 6:
            fx = self.camera_info.k[0]
            fy = self.camera_info.k[4]
            cx = self.camera_info.k[2]
            cy = self.camera_info.k[5]

        x = (u - cx) / fx * depth_m
        y = (v - cy) / fy * depth_m
        z = depth_m

        # 真实项目：在这里调用 tf2，把 camera_frame 点转换到 base_link。
        return x, y, z


def main(args=None) -> int:
    if rclpy is None:
        print('rclpy is not available. Please source ROS 2 Humble environment first.')
        return 0

    rclpy.init(args=args)
    node = PerceptionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
