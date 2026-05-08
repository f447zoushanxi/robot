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
// 模块说明：robot_nav — 导航服务节点（nav_server_node）
// =============================================================================
// 这个节点管理"家庭地点"（locations.yaml）并提供导航到交付点的服务。
//
// 主要功能：
//   1) 启动时从 YAML 文件加载家庭地点（例如：客厅、餐桌旁、卧室）。
//   2) 提供 /nav/go_handover_spot 服务：导航到"交付点"（例如餐桌旁）。
//
// 什么是 locations.yaml？
//   这是一个配置文件，记录家里各个位置的坐标（x, y, yaw）。
//   例如：
//     locations:
//       - {name: 客厅, x: 0.0, y: 0.0, yaw: 0.0}
//       - {name: 餐桌旁, x: 2.5, y: 1.0, yaw: 1.57}
//
//   机器人用这些坐标向 Nav2 发送导航目标，Nav2 再规划路径并驱动底盘。
//
// 服务（Services）：
//   - /nav/go_handover_spot [std_srvs/Trigger]  导航到"交付点"
//     响应 success=true：找到交付点，开始导航（骨架中直接返回结果）
//     响应 success=false：locations.yaml 未加载或找不到交付点
//
// 关键参数（可通过 launch 文件传入）：
//   - handover_spot  (string, 默认 "餐桌旁")：交付点在 YAML 里的名字
//   - locations_file (string, 默认 "")      ：locations.yaml 的完整路径
// =============================================================================

#include <memory>
#include <string>

#include "robot_nav/location_manager.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

// NavServerNode：导航服务节点
class NavServerNode : public rclcpp::Node
{
public:
  // 构造函数：加载地点文件，注册导航服务
  NavServerNode()
  : Node("nav_server_node")
  {
    // 读取参数：交付点名称（必须在 YAML 文件里存在）
    handover_spot_ = declare_parameter<std::string>("handover_spot", "餐桌旁");
    // 读取参数：地点配置文件路径（空字符串表示不加载）
    locations_file_ = declare_parameter<std::string>("locations_file", "");

    // 如果配置了文件路径，则尝试加载地点列表
    if (!locations_file_.empty()) {
      loaded_ = manager_.load_from_yaml(locations_file_);
    }

    // 注册"导航到交付点"服务
    // executor_node 完成"找到用户"后会调用这个服务，把水送到指定位置
    go_handover_srv_ = create_service<std_srvs::srv::Trigger>(
      "/nav/go_handover_spot",
      [this](
        const std::shared_ptr<std_srvs::srv::Trigger::Request>,
        std::shared_ptr<std_srvs::srv::Trigger::Response> resp)
      {
        // 检查地点列表是否已加载
        if (!loaded_) {
          resp->success = false;
          resp->message = "locations.yaml not loaded";
          return;
        }

        // 检查交付点名称是否在列表中存在
        if (!manager_.has(handover_spot_)) {
          resp->success = false;
          resp->message = "handover_spot not found in locations";
          return;
        }

        // 获取交付点坐标，返回成功（骨架：真实项目会发送 Nav2 goal）
        const auto loc = manager_.get(handover_spot_);
        resp->success = true;
        resp->message = "Stub nav accepted -> " + loc.name + " (" +
        std::to_string(loc.x) + "," + std::to_string(loc.y) + ")";
      });

    RCLCPP_INFO(
      get_logger(), "robot_nav skeleton started. locations_file=%s loaded=%s",
      locations_file_.c_str(), loaded_ ? "true" : "false");
  }

private:
  std::string handover_spot_;         // 交付点名称
  std::string locations_file_;        // 地点配置文件路径
  bool loaded_{false};                // 地点列表是否成功加载
  robot_nav::LocationManager manager_;  // 地点管理器（负责 YAML 解析和查找）
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr go_handover_srv_;
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NavServerNode>());
  rclcpp::shutdown();
  return 0;
}
