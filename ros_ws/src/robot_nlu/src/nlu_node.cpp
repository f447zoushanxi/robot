#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

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
        out.data = parse_to_json(msg->data);
        command_pub_->publish(out);
      });
  }

private:
  std::string parse_to_json(const std::string & text)
  {
    // 规则优先：保证高频家庭指令无需依赖大模型也能稳定运行。
    if (text.find("停") != std::string::npos) {
      return R"({"intent":"stop","slots":{},"auth":{"requested_role":"any","require_confirmation":false}})";
    }
    if (text.find("记住我的声音") != std::string::npos) {
      return R"({"intent":"enroll_owner_voice","slots":{},"auth":{"requested_role":"owner","require_confirmation":true}})";
    }
    if (text.find("记住我") != std::string::npos) {
      return R"({"intent":"enroll_owner","slots":{},"auth":{"requested_role":"owner","require_confirmation":true}})";
    }
    if (text.find("我在") != std::string::npos) {
      return R"({"intent":"remember_location","slots":{"user_location":"unknown"},"auth":{"requested_role":"owner","require_confirmation":false}})";
    }
    if (text.find("去") != std::string::npos) {
      return R"({"intent":"navigate","slots":{"target":"living_room"},"auth":{"requested_role":"guest","require_confirmation":false}})";
    }
    if (text.find("递水") != std::string::npos || text.find("拿水") != std::string::npos) {
      return R"({"intent":"deliver_water","slots":{"object":"bottle","deliver_to":"person_nearby"},"auth":{"requested_role":"owner","require_confirmation":true}})";
    }

    // 兜底：真实项目中调用 Ollama HTTP API，并强制其返回结构化 JSON。
    // 此处仅保留接口形态，避免把外部依赖硬编码到骨架中。
    return R"({"intent":"unknown","slots":{},"auth":{"requested_role":"guest","require_confirmation":false},"source":"ollama_fallback_stub"})";
  }

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
