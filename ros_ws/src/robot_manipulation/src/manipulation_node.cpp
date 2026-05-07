#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

class ManipulationNode : public rclcpp::Node
{
public:
  ManipulationNode() : Node("manipulation_node")
  {
    sim_mode_ = declare_parameter<bool>("sim_mode", true);

    pick_srv_ = create_service<std_srvs::srv::Trigger>(
      "/manipulation/pick_bottle",
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
      std::shared_ptr<std_srvs::srv::Trigger::Response> resp) {
        resp->success = true;
        resp->message = sim_mode_ ? "pick_bottle simulated" : "pick_bottle sent to arm driver";
      });

    handover_srv_ = create_service<std_srvs::srv::Trigger>(
      "/manipulation/hand_over",
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
      std::shared_ptr<std_srvs::srv::Trigger::Response> resp) {
        resp->success = true;
        resp->message = sim_mode_ ? "hand_over simulated" : "hand_over sent to arm driver";
      });
  }

private:
  bool sim_mode_{true};
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr pick_srv_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr handover_srv_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ManipulationNode>());
  rclcpp::shutdown();
  return 0;
}
