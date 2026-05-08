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

// =============================================================================
// 模块说明：robot_nlu — 自然语言理解节点（nlu_node）
// =============================================================================
// NLU = Natural Language Understanding（自然语言理解）
//
// 这个节点的职责：
//   把用户说的话（语音文字）转换成机器人能理解的结构化指令（JSON 格式）。
//
//   例如：
//     输入（语音文字）："/voice/asr_text" -> "请给我递水"
//     输出（JSON 指令）："/nlu/command_json" -> {"intent":"deliver_water",...}
//
// 数据流：
//   语音模块（robot_voice）发布 /voice/asr_text
//   NLU 节点订阅该话题，调用 parse_to_json() 解析文字
//   解析结果发布到 /nlu/command_json
//   执行器节点（robot_executor）订阅 /nlu/command_json 并执行对应动作
//
// 话题（Topics）：
//   - 订阅 /voice/asr_text   [std_msgs/String]  接收语音识别文字
//   - 发布 /nlu/command_json [std_msgs/String]  发布解析后的 JSON 指令
// =============================================================================

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_nlu/nlu_parser.hpp"
#include "std_msgs/msg/string.hpp"

// NluNode：自然语言理解节点
class NluNode : public rclcpp::Node
{
public:
  // 构造函数：注册话题订阅和发布
  NluNode()
  : Node("nlu_node")
  {
    // 创建发布者，用于发布解析好的 JSON 指令
    command_pub_ = create_publisher<std_msgs::msg::String>("/nlu/command_json", 10);

    // 订阅语音识别结果（ASR = Automatic Speech Recognition 自动语音识别）
    // 每收到一条文字，立即调用 parse_to_json() 并发布解析结果
    asr_sub_ = create_subscription<std_msgs::msg::String>(
      "/voice/asr_text", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        std_msgs::msg::String out;
        // parse_to_json：把中文指令转成 JSON 字符串（实现在 nlu_parser.cpp）
        out.data = robot_nlu::parse_to_json(msg->data);
        command_pub_->publish(out);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr asr_sub_;   // 订阅语音文字
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_pub_;  // 发布 JSON 指令
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NluNode>());
  rclcpp::shutdown();
  return 0;
}
