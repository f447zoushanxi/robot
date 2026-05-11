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
// 模块说明：robot_identity — 身份识别节点（identity_node）
// =============================================================================
// 这个节点负责管理"谁是机器人的主人"以及"当前说话的人是谁"。
//
// 两个核心概念：
//   1) 主人注册（Enroll）：第一次告诉机器人"这是主人"的过程。
//      - 为了安全，注册时需要按下物理按钮（防止陌生人偷偷注册）。
//      - 注册成功后，机器人会记录主人的 ID，以后识别时对比。
//
//   2) 主人识别（Recognize）：
//      - 真实项目：融合人脸识别 + 声纹识别，判断说话的人是主人还是访客。
//      - 当前骨架：如果已注册主人则返回 "owner"，否则返回 "unknown"。
//
// 角色系统：
//   - owner  ：主人，可以执行所有指令（包括"递水"等需要确认的指令）
//   - guest  ：访客，只能执行部分指令（如"去客厅"）
//   - unknown：未识别，只能执行基本指令（如"停"）
//
// 服务（Services）：
//   - /identity/enroll_owner    [robot_msgs/EnrollOwner]  注册主人
//   - /identity/recognize_owner [std_srvs/Trigger]         识别当前用户
//
// 话题（Topics）：
//   - 发布 /identity/current_role [std_msgs/String]  当前识别到的角色
//
// 关键参数（可通过 launch 文件传入）：
//   - owner_enrolled (bool, 默认 false)：是否已有主人注册
//   - require_button_for_first_enroll (bool, 默认 true)：首次注册是否需要物理按钮
// =============================================================================

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_identity/enroll_policy.hpp"
#include "robot_msgs/srv/enroll_owner.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"

// IdentityNode：身份识别节点
class IdentityNode : public rclcpp::Node
{
public:
  // 构造函数：初始化参数和服务
  IdentityNode()
  : Node("identity_node")
  {
    // 读取参数：是否已有主人注册（重启后可从配置文件恢复）
    owner_enrolled_ = declare_parameter<bool>("owner_enrolled", false);
    // 读取参数：首次注册是否需要物理按钮确认（安全保护）
    require_button_ = declare_parameter<bool>("require_button_for_first_enroll", true);

    // 创建发布者：发布当前识别到的角色
    role_pub_ = create_publisher<std_msgs::msg::String>("/identity/current_role", 10);

    // 注册主人服务：其他节点调用这个服务来注册主人身份
    enroll_srv_ = create_service<robot_msgs::srv::EnrollOwner>(
      "/identity/enroll_owner",
      [this](
        const std::shared_ptr<robot_msgs::srv::EnrollOwner::Request> req,
        std::shared_ptr<robot_msgs::srv::EnrollOwner::Response> resp)
      {
        // 调用策略函数决定是否允许注册（见 enroll_policy.cpp）
        if (!robot_identity::allow_enroll(
          owner_enrolled_, require_button_, req->require_physical_confirm))
        {
          // 真实项目：读取 GPIO/MCU 按钮信号，窗口内按下才放行。
          // 当前骨架：拒绝注册，提示需要物理确认
          resp->accepted = false;
          resp->message = "Waiting physical button confirmation window.";
          return;
        }

        // 注册成功：记录主人已注册，分配 ID
        owner_enrolled_ = true;
        resp->accepted = true;
        resp->owner_id = "owner_001";
        resp->message = "Owner enrollment accepted (stub).";
      });

    // 识别主人服务：判断当前说话/出现的人是否是主人
    recognize_srv_ = create_service<std_srvs::srv::Trigger>(
      "/identity/recognize_owner",
      [this](
        const std::shared_ptr<std_srvs::srv::Trigger::Request>,
        std::shared_ptr<std_srvs::srv::Trigger::Response> resp)
      {
        // 真实项目：融合 face/voice embedding 匹配结果。
        // 当前骨架：已注册则认为是 owner，否则是 unknown
        const std::string role = owner_enrolled_ ? "owner" : "unknown";
        std_msgs::msg::String out;
        out.data = role;
        role_pub_->publish(out);  // 发布识别结果，其他节点可订阅

        resp->success = true;
        resp->message = role;
      });
  }

private:
  bool owner_enrolled_{false};  // 是否已有主人注册
  bool require_button_{true};   // 首次注册是否需要物理按钮

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr role_pub_;
  rclcpp::Service<robot_msgs::srv::EnrollOwner>::SharedPtr enroll_srv_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr recognize_srv_;
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IdentityNode>());
  rclcpp::shutdown();
  return 0;
}
