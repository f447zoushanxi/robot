// Minimal lifecycle_node.cpp stub so the C++ package can build in CI even
// if full implementation is added later.

#include <memory>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("lifecycle_node_stub");
  RCLCPP_INFO(node->get_logger(), "lifecycle_node stub started");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
