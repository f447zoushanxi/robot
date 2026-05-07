#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_msgs/srv/enroll_owner.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"

class IdentityNode : public rclcpp::Node
{
public:
  IdentityNode() : Node("identity_node")
  {
    owner_enrolled_ = declare_parameter<bool>("owner_enrolled", false);
    require_button_ = declare_parameter<bool>("require_button_for_first_enroll", true);

    role_pub_ = create_publisher<std_msgs::msg::String>("/identity/current_role", 10);

    enroll_srv_ = create_service<robot_msgs::srv::EnrollOwner>(
      "/identity/enroll_owner",
      [this](const std::shared_ptr<robot_msgs::srv::EnrollOwner::Request> req,
      std::shared_ptr<robot_msgs::srv::EnrollOwner::Response> resp) {
        if (!owner_enrolled_ && req->require_physical_confirm && require_button_) {
          // 真实项目：读取 GPIO/MCU 按钮信号，窗口内按下才放行。
          resp->accepted = false;
          resp->message = "Waiting physical button confirmation window.";
          return;
        }

        owner_enrolled_ = true;
        resp->accepted = true;
        resp->owner_id = "owner_001";
        resp->message = "Owner enrollment accepted (stub).";
      });

    recognize_srv_ = create_service<std_srvs::srv::Trigger>(
      "/identity/recognize_owner",
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
      std::shared_ptr<std_srvs::srv::Trigger::Response> resp) {
        // 真实项目：融合 face/voice embedding 匹配结果。
        const std::string role = owner_enrolled_ ? "owner" : "unknown";
        std_msgs::msg::String out;
        out.data = role;
        role_pub_->publish(out);

        resp->success = true;
        resp->message = role;
      });
  }

private:
  bool owner_enrolled_{false};
  bool require_button_{true};

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr role_pub_;
  rclcpp::Service<robot_msgs::srv::EnrollOwner>::SharedPtr enroll_srv_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr recognize_srv_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IdentityNode>());
  rclcpp::shutdown();
  return 0;
}
