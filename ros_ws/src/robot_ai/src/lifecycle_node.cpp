#include "robot_ai/lifecycle_node.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace robot_ai
{

AiLifecycleNode::AiLifecycleNode(const std::string & name)
: LifecycleNode(name)
{
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn AiLifecycleNode::on_configure(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_logger(), "AiLifecycleNode on_configure");
  return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn AiLifecycleNode::on_activate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_logger(), "AiLifecycleNode on_activate");
  return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn AiLifecycleNode::on_deactivate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_logger(), "AiLifecycleNode on_deactivate");
  return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn AiLifecycleNode::on_cleanup(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(get_logger(), "AiLifecycleNode on_cleanup");
  return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

} // namespace robot_ai

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<robot_ai::AiLifecycleNode>("robot_ai_lifecycle");
  RCLCPP_INFO(node->get_logger(), "robot_ai lifecycle node starting");
  rclcpp::spin(node->get_node_base_interface());
  rclcpp::shutdown();
  return 0;
}
