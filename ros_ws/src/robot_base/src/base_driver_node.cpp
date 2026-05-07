#include <chrono>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

using namespace std::chrono_literals;

class BaseDriverNode : public rclcpp::Node
{
public:
  BaseDriverNode() : Node("base_driver_node")
  {
    use_stub_ = this->declare_parameter<bool>("use_stub", true);
    timeout_ms_ = this->declare_parameter<int>("cmd_timeout_ms", 200);

    cmd_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        last_cmd_ = *msg;
        last_cmd_time_ = this->now();
      });

    odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);
    estop_pub_ = this->create_publisher<std_msgs::msg::Bool>("/estop", 10);

    timer_ = this->create_wall_timer(50ms, std::bind(&BaseDriverNode::on_timer, this));

    RCLCPP_INFO(
      get_logger(),
      "robot_base started (stub=%s). Serial protocol and real IO are intentionally placeholders.",
      use_stub_ ? "true" : "false");
  }

private:
  void on_timer()
  {
    const auto now = this->now();
    const bool timeout = (now - last_cmd_time_).nanoseconds() > static_cast<int64_t>(timeout_ms_) * 1000000LL;

    geometry_msgs::msg::Twist safe_cmd = last_cmd_;
    if (timeout) {
      // 核心安全逻辑：超时刹车。
      safe_cmd.linear.x = 0.0;
      safe_cmd.angular.z = 0.0;
    }

    nav_msgs::msg::Odometry odom;
    odom.header.stamp = now;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    odom.twist.twist = safe_cmd;
    odom_pub_->publish(odom);

    std_msgs::msg::Bool estop;
    estop.data = false;
    estop_pub_->publish(estop);
  }

  bool use_stub_{true};
  int timeout_ms_{200};
  rclcpp::Time last_cmd_time_{0, 0, RCL_ROS_TIME};
  geometry_msgs::msg::Twist last_cmd_{};

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr estop_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BaseDriverNode>());
  rclcpp::shutdown();
  return 0;
}
