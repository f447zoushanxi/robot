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
// 模块说明：robot_manipulation — 机械臂操作节点（manipulation_node）
// =============================================================================
// 这个节点控制机械臂完成"抓水瓶"和"递水给用户"两个动作。
//
// 当前状态（骨架 + sim_mode）：
//   节点提供了真实的 ROS2 服务接口，但具体的机械臂控制是"模拟"的：
//   - sim_mode=true（默认）：服务直接返回"成功"，不发送任何硬件指令。
//   - sim_mode=false：理论上应发送指令给机械臂驱动，但真实驱动代码待实现。
//
// 服务（Services）：
//   - /manipulation/pick_bottle [std_srvs/Trigger]  抓取水瓶
//     请求：无参数（Trigger 类型）
//     响应：success=true/false, message（描述结果）
//
//   - /manipulation/hand_over   [std_srvs/Trigger]  递水给用户
//     请求：无参数
//     响应：success=true/false, message
//
// 关键参数（可通过 launch 文件传入）：
//   - sim_mode (bool, 默认 true)：true = 模拟模式，false = 真实机械臂
//
// 数据流（executor 调用顺序）：
//   executor_node 进入 PICK_BOTTLE 状态 → 调用 /manipulation/pick_bottle
//   executor_node 进入 HAND_OVER 状态  → 调用 /manipulation/hand_over
// =============================================================================

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

// ManipulationNode：机械臂操作节点
class ManipulationNode : public rclcpp::Node
{
public:
  // 构造函数：读取参数，注册服务
  ManipulationNode()
  : Node("manipulation_node")
  {
    // 读取模式参数：true = 模拟，false = 真实机械臂
    sim_mode_ = declare_parameter<bool>("sim_mode", true);

    // 注册"抓取水瓶"服务
    // executor_node 在 PICK_BOTTLE 状态时调用此服务
    pick_srv_ = create_service<std_srvs::srv::Trigger>(
      "/manipulation/pick_bottle",
      [this](
        const std::shared_ptr<std_srvs::srv::Trigger::Request>,
        std::shared_ptr<std_srvs::srv::Trigger::Response> resp)
      {
        resp->success = true;
        // 根据模式返回不同的消息（方便日志区分）
        resp->message = sim_mode_ ? "pick_bottle simulated" : "pick_bottle sent to arm driver";
      });

    // 注册"递水给用户"服务
    // executor_node 在 HAND_OVER 状态时调用此服务
    handover_srv_ = create_service<std_srvs::srv::Trigger>(
      "/manipulation/hand_over",
      [this](
        const std::shared_ptr<std_srvs::srv::Trigger::Request>,
        std::shared_ptr<std_srvs::srv::Trigger::Response> resp)
      {
        resp->success = true;
        resp->message = sim_mode_ ? "hand_over simulated" : "hand_over sent to arm driver";
      });
  }

private:
  bool sim_mode_{true};  // 是否为模拟模式

  // --- ROS2 服务 ---
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr pick_srv_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr handover_srv_;
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ManipulationNode>());
  rclcpp::shutdown();
  return 0;
}
