"""
tools/data/extract_images_from_bag.py

Subscribe to image topics and save images to disk. Designed to be run while
ros2 bag play is running or directly subscribing to live topics.

Usage:
  python tools/data/extract_images_from_bag.py --out data/scene1 --image-topic /camera/color/image_raw --depth-topic /camera/aligned_depth_to_color/image_raw

Note: Requires ROS2 python packages and cv_bridge.
"""
import argparse
import os

try:
    import rclpy
    from rclpy.node import Node
    from sensor_msgs.msg import Image
    from cv_bridge import CvBridge
    import cv2
except Exception:
    rclpy = None

class SaverNode(Node):
    def __init__(self, outdir, img_topic, depth_topic):
        super().__init__('bag_image_saver')
        self.outdir = outdir
        self.bridge = CvBridge()
        self.count = 0
        self.create_subscription(Image, img_topic, self.cb_img, 10)
        if depth_topic:
            self.create_subscription(Image, depth_topic, self.cb_depth, 10)

    def cb_img(self, msg):
        cv = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        fn = os.path.join(self.outdir, f'{self.count:06d}.jpg')
        cv2.imwrite(fn, cv)
        self.get_logger().info(f'wrote {fn}')
        self.count += 1

    def cb_depth(self, msg):
        # optional: save depth as 16-bit PNG
        pass

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--out', required=True)
    p.add_argument('--image-topic', default='/camera/color/image_raw')
    p.add_argument('--depth-topic', default='/camera/aligned_depth_to_color/image_raw')
    args = p.parse_args()

    if rclpy is None:
        print('This script requires ROS2 python packages and cv_bridge. Run in environment with ROS2 sourced.')
        return
    os.makedirs(args.out, exist_ok=True)
    rclpy.init()
    node = SaverNode(args.out, args.image_topic, args.depth_topic)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
