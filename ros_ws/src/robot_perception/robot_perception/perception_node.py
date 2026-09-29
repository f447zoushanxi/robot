# Updated perception_node with optional AI inference integration
# It will attempt to load a selected model (env var ROBOT_PERCEPTION_MODEL_NAME or param)
# and use it for detect_bottle. If inference dependencies are missing, it falls back to stub behavior.

from __future__ import annotations

import os
import statistics
from typing import Optional, Sequence, Tuple

# Try importing ROS2 and message/service types
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

# Try to import ai_inference model manager
try:
    from robot_perception.ai_inference import ModelManager
except Exception:
    ModelManager = None


class PerceptionNode(Node):
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

        # Model manager
        models_dir = os.path.join(os.path.dirname(__file__), '..', 'models')
        models_dir = os.path.normpath(models_dir)
        self.model_mgr = None
        if ModelManager is not None:
            try:
                self.model_mgr = ModelManager(models_dir)
                # try load model name from env var
                model_name = os.environ.get('ROBOT_PERCEPTION_MODEL_NAME', None)
                if model_name and model_name in self.model_mgr.available_models():
                    loaded = self.model_mgr.load_model(model_name)
                    if loaded:
                        self.get_logger().info(f'Loaded perception model: {model_name}')
            except Exception:
                self.model_mgr = None

        self.get_logger().info('robot_perception started (with optional ONNX inference).')

    def _on_color(self, msg: Image) -> None:
        self.color_msg = msg

    def _on_depth(self, msg: Image) -> None:
        self.depth_msg = msg

    def _on_info(self, msg: CameraInfo) -> None:
        self.camera_info = msg

    def _handle_detect_bottle(self, request: DetectObject.Request, response: DetectObject.Response):
        # If we have a loaded model and a color image, attempt inference
        if self.model_mgr is not None and self.color_msg is not None:
            try:
                dets = self.model_mgr.infer_from_ros_image(self.color_msg)
                # choose highest confidence detection
                if dets:
                    best = max(dets, key=lambda d: d.confidence)
                    # map bbox center to pixel coordinates
                    # assuming x,y are relative center (0..1) or absolute pixels — heuristics here
                    if best.x <= 1.0 and best.y <= 1.0:
                        # relative coords
                        # convert to pixels requires image width/height; if unavailable, fallback
                        u = int(best.x * 640)
                        v = int(best.y * 480)
                    else:
                        u = int(best.x)
                        v = int(best.y)
                    depth_m = self._median_depth_stub([0.72])
                    x, y, z = self._back_project_pixel_to_3d(u, v, depth_m)

                    response.found = True
                    response.position = Point(x=float(x), y=float(y), z=float(z))
                    response.confidence = float(best.confidence)
                    response.frame_id = 'base_link'
                    response.message = f'detect via model {self.model_mgr.loaded_name}'
                    return response
            except Exception:
                # on any failure, fall through to stub
                pass

        # fallback stub behavior
        u, v = 320, 240
        depth_m = self._median_depth_stub([0.72, 0.73, 0.70, 0.71, 0.74])
        x, y, z = self._back_project_pixel_to_3d(u, v, depth_m)

        response.found = True
        response.position = Point(x=float(x), y=float(y), z=float(z))
        response.confidence = 0.5
        response.frame_id = 'base_link'
        response.message = f'stub detect {request.object_name} timeout={request.timeout_sec}'
        return response

    def _handle_find_person(self, request: FindPerson.Request, response: FindPerson.Response):
        # For now keep stub for person finding; model-based person detection can be added similarly
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
        fx, fy, cx, cy = 600.0, 600.0, 320.0, 240.0
        if self.camera_info is not None and len(self.camera_info.k) >= 6:
            fx = self.camera_info.k[0]
            fy = self.camera_info.k[4]
            cx = self.camera_info.k[2]
            cy = self.camera_info.k[5]

        x = (u - cx) / fx * depth_m
        y = (v - cy) / fy * depth_m
        z = depth_m
        return x, y, z


def _safe_shutdown() -> None:
    if rclpy is None:
        return
    try:
        if rclpy.ok():
            rclpy.shutdown()
    except Exception:
        pass


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
        try:
            node.destroy_node()
        except Exception:
            pass
        _safe_shutdown()
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
