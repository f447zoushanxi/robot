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

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class VoiceBridgeNode : public rclcpp::Node
{
public:
  VoiceBridgeNode()
  : Node("voice_bridge_node")
  {
    asr_out_pub_ = create_publisher<std_msgs::msg::String>("/voice/asr_text", 10);

    asr_in_sub_ = create_subscription<std_msgs::msg::String>(
      "/voice/raw_text", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        // 占位桥接：真实系统可由外部 ASR/TTS 进程通过 topic 或 websocket 接入。
        asr_out_pub_->publish(*msg);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr asr_in_sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr asr_out_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VoiceBridgeNode>());
  rclcpp::shutdown();
  return 0;
}
