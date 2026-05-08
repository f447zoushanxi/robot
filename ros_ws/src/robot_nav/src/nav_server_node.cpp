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

#include "robot_nav/location_manager.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"

class NavServerNode : public rclcpp::Node
{
public:
  NavServerNode()
  : Node("nav_server_node")
  {
    handover_spot_ = declare_parameter<std::string>("handover_spot", "餐桌旁");
    locations_file_ = declare_parameter<std::string>("locations_file", "");
    if (!locations_file_.empty()) {
      loaded_ = manager_.load_from_yaml(locations_file_);
    }

    go_handover_srv_ = create_service<std_srvs::srv::Trigger>(
      "/nav/go_handover_spot",
      [this](
        const std::shared_ptr<std_srvs::srv::Trigger::Request>,
        std::shared_ptr<std_srvs::srv::Trigger::Response> resp)
      {
        if (!loaded_) {
          resp->success = false;
          resp->message = "locations.yaml not loaded";
          return;
        }
        if (!manager_.has(handover_spot_)) {
          resp->success = false;
          resp->message = "handover_spot not found in locations";
          return;
        }
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
  std::string handover_spot_;
  std::string locations_file_;
  bool loaded_{false};
  robot_nav::LocationManager manager_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr go_handover_srv_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NavServerNode>());
  rclcpp::shutdown();
  return 0;
}
