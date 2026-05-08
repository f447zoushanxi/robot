// Copyright (c) 2026.
// Copyright 2026 f447zoushanxi
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

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_nlu/nlu_parser.hpp"
#include "std_msgs/msg/string.hpp"

class NluNode : public rclcpp::Node
{
public:
  NluNode()
  : Node("nlu_node")
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
