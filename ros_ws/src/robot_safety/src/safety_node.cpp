// Copyright (c) 2026.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <algorithm>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class SafetyNode : public rclcpp::Node
{
public:
  SafetyNode()
  : Node("safety_node")
  {
    max_linear_ = declare_parameter<double>("max_linear", 0.35);
    max_angular_ = declare_parameter<double>("max_angular", 1.0);

    cmd_in_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel_raw", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        last_cmd_ = *msg;
        publish_safe_cmd();
      });

    estop_sub_ = create_subscription<std_msgs::msg::Bool>(
      "/estop", 10,
      [this](const std_msgs::msg::Bool::SharedPtr msg) {
        estop_ = msg->data;
        publish_safe_cmd();
      });

    cmd_out_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
  }

private:
  void publish_safe_cmd()
  {
    geometry_msgs::msg::Twist out = last_cmd_;
    if (estop_) {
      out.linear.x = 0.0;
      out.angular.z = 0.0;
    } else {
      out.linear.x = std::clamp(out.linear.x, -max_linear_, max_linear_);
      out.angular.z = std::clamp(out.angular.z, -max_angular_, max_angular_);
    }
    cmd_out_pub_->publish(out);
  }

  double max_linear_{0.35};
  double max_angular_{1.0};
  bool estop_{false};
  geometry_msgs::msg::Twist last_cmd_{};

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_in_sub_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr estop_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_out_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SafetyNode>());
  rclcpp::shutdown();
  return 0;
}
