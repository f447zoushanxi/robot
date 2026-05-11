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
// 模块说明：robot_safety — 安全节点（safety_node）
// =============================================================================
// 这个节点是机器人速度的"安全守门员"。
// 所有速度指令都必须经过这里，不符合安全要求的会被修改或清零。
//
// 工作原理（两重保护）：
//   1) 急停保护（E-Stop）：
//      如果底盘（robot_base）发布急停信号（/estop = true），
//      不管上游发来什么速度，这个节点都把速度强制清零。
//      例如：有人按了急停按钮，机器人必须立刻停下。
//
//   2) 速度限幅（Clamp）：
//      即使没有急停，也会把速度限制在安全范围内：
//        线速度（前进/后退）：不超过 max_linear（默认 0.35 m/s）
//        角速度（旋转）：不超过 max_angular（默认 1.0 rad/s）
//      这防止上游误发过大速度导致机器人失控。
//
// 速度链路（数据流）：
//   executor_node 发布 /cmd_vel_raw（原始速度）
//   → safety_node 检查急停 + 限幅
//   → 发布 /cmd_vel（安全速度）
//   → base_driver_node 订阅 /cmd_vel 并驱动底盘
//
// 话题（Topics）：
//   - 订阅 /cmd_vel_raw   [geometry_msgs/Twist]  接收原始速度指令
//   - 订阅 /estop         [std_msgs/Bool]         接收急停信号
//   - 发布 /cmd_vel       [geometry_msgs/Twist]  发布安全速度指令
//
// 关键参数（可通过 launch 文件传入）：
//   - max_linear  (double, 默认 0.35)：最大线速度，单位 米/秒
//   - max_angular (double, 默认 1.0) ：最大角速度，单位 弧度/秒
// =============================================================================

#include <algorithm>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

// SafetyNode：速度安全节点
class SafetyNode : public rclcpp::Node
{
public:
  // 构造函数：初始化参数、话题订阅和发布
  SafetyNode()
  : Node("safety_node")
  {
    // 读取安全速度限制参数
    max_linear_ = declare_parameter<double>("max_linear", 0.35);   // 最大线速度（米/秒）
    max_angular_ = declare_parameter<double>("max_angular", 1.0);  // 最大角速度（弧度/秒）

    // 订阅原始速度指令（来自 executor_node 或其他上游节点）
    // 每收到一次，立刻检查安全性并转发
    cmd_in_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel_raw", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        last_cmd_ = *msg;         // 保存最新速度指令
        publish_safe_cmd();       // 立刻执行安全检查并发布
      });

    // 订阅急停信号（来自 base_driver_node 的底盘状态）
    // 急停信号为 true 时，所有速度清零
    estop_sub_ = create_subscription<std_msgs::msg::Bool>(
      "/estop", 10,
      [this](const std_msgs::msg::Bool::SharedPtr msg) {
        estop_ = msg->data;       // 更新急停状态
        publish_safe_cmd();       // 急停状态变化时，立刻重新计算并发布安全速度
      });

    // 创建发布者：发布通过安全检查后的速度指令
    cmd_out_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
  }

private:
  // publish_safe_cmd：对最新速度指令进行安全检查，然后发布
  void publish_safe_cmd()
  {
    geometry_msgs::msg::Twist out = last_cmd_;

    if (estop_) {
      // 急停触发：强制停车（线速度和角速度都清零）
      out.linear.x = 0.0;
      out.angular.z = 0.0;
    } else {
      // 正常运行：对速度做限幅（clamp = 强制限制在 [min, max] 范围内）
      // 例如：上游发了 1.0 m/s，限幅后变为 0.35 m/s
      out.linear.x = std::clamp(out.linear.x, -max_linear_, max_linear_);
      out.angular.z = std::clamp(out.angular.z, -max_angular_, max_angular_);
    }

    // 发布安全速度指令，底盘节点订阅 /cmd_vel 并执行
    cmd_out_pub_->publish(out);
  }

  // --- 安全参数 ---
  double max_linear_{0.35};    // 最大线速度（米/秒）
  double max_angular_{1.0};    // 最大角速度（弧度/秒）
  bool estop_{false};          // 急停状态（false = 正常，true = 急停）
  geometry_msgs::msg::Twist last_cmd_{};  // 上游发来的最新速度指令

  // --- ROS2 通信对象 ---
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_in_sub_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr estop_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_out_pub_;
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SafetyNode>());
  rclcpp::shutdown();
  return 0;
}
