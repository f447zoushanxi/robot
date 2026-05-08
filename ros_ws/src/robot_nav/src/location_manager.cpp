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

#include "robot_nav/location_manager.hpp"

#include <yaml-cpp/yaml.h>

namespace robot_nav
{

bool LocationManager::load_from_yaml(const std::string & file_path)
{
  YAML::Node root;
  try {
    root = YAML::LoadFile(file_path);
  } catch (const YAML::Exception &) {
    return false;
  }

  const auto locations = root["locations"];
  if (!locations || !locations.IsSequence()) {
    return false;
  }

  locations_.clear();
  for (const auto & item : locations) {
    if (!item.IsMap()) {
      continue;
    }
    const auto name_node = item["name"];
    const auto x_node = item["x"];
    const auto y_node = item["y"];
    const auto yaw_node = item["yaw"];
    if (!name_node || !x_node || !y_node || !yaw_node) {
      continue;
    }

    try {
      NamedLocation loc;
      loc.name = name_node.as<std::string>();
      loc.x = x_node.as<double>();
      loc.y = y_node.as<double>();
      loc.yaw = yaw_node.as<double>();
      if (loc.name.empty()) {
        continue;
      }
      locations_[loc.name] = loc;
    } catch (const YAML::Exception &) {
      continue;
    }
  }
  return !locations_.empty();
}

bool LocationManager::has(const std::string & key) const
{
  return locations_.find(key) != locations_.end();
}

NamedLocation LocationManager::get(const std::string & key) const
{
  auto it = locations_.find(key);
  if (it != locations_.end()) {
    return it->second;
  }
  return NamedLocation{};
}

}  // namespace robot_nav
