#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "robot_nlu/nlu_parser.hpp"

class NluNode : public rclcpp::Node
{
public:
  NluNode() : Node("nlu_node")
  {
    command_pub_ = create_publisher<std_msgs::msg::String>("/nlu/command_json", 10);
    asr_sub_ = create_subscription<std_msgs::msg::String>(
      "/voice/asr_text", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        std_msgs::msg::String out;
        out.data = robot_nlu::parse_to_json(msg->data);
        command_pub_->publish(out);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr asr_sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NluNode>());
  rclcpp::shutdown();
  return 0;
}
