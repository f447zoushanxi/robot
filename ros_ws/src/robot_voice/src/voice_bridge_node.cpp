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
// 模块说明：robot_voice — 语音桥接节点（voice_bridge_node）
// =============================================================================
// 这个节点是语音输入的"入口"。
//
// 背景：
//   真实系统中，语音识别（ASR = Automatic Speech Recognition）通常由独立的
//   进程完成（例如讯飞/百度 SDK、Whisper 等），识别结果需要传入 ROS2 系统。
//
//   这个桥接节点提供了统一的接入方式：
//   - 外部 ASR 进程把识别结果发布到 /voice/raw_text
//   - 或者开发者手动发布文字（测试时很有用！）：
//       ros2 topic pub /voice/raw_text std_msgs/msg/String "{data: '请给我递水'}" -1
//
//   桥接节点接收后，原样转发到 /voice/asr_text，NLU 节点从这里订阅。
//
// 话题（Topics）：
//   - 订阅 /voice/raw_text   [std_msgs/String]  外部 ASR 或手动输入
//   - 发布 /voice/asr_text   [std_msgs/String]  转发给 NLU 节点
//
// 注意：当前为"直通"实现（raw_text → asr_text 不做任何处理）。
//       真实项目可在这里加：降噪过滤、语言检测、置信度过滤等。
// =============================================================================

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// VoiceBridgeNode：语音桥接节点（占位/可替换）
class VoiceBridgeNode : public rclcpp::Node
{
public:
  // 构造函数：注册话题订阅和发布
  VoiceBridgeNode()
  : Node("voice_bridge_node")
  {
    // 创建发布者：把语音文字转发给 NLU 节点
    asr_out_pub_ = create_publisher<std_msgs::msg::String>("/voice/asr_text", 10);

    // 订阅外部输入的语音文字（可以是 ASR 进程，也可以是手动命令）
    asr_in_sub_ = create_subscription<std_msgs::msg::String>(
      "/voice/raw_text", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        // 占位桥接：真实系统可由外部 ASR/TTS 进程通过 topic 或 websocket 接入。
        // 当前直接原样转发，不做任何处理
        asr_out_pub_->publish(*msg);
      });
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr asr_in_sub_;  // 接收原始文字
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr asr_out_pub_;    // 转发给 NLU
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VoiceBridgeNode>());
  rclcpp::shutdown();
  return 0;
}
