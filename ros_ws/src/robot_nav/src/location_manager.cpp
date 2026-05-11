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
// 模块说明：robot_nav — 地点管理器实现（location_manager.cpp）
// =============================================================================
// 这个文件实现从 YAML 文件加载家庭地点列表，并提供查找功能。
//
// YAML 文件格式（locations.yaml）：
//   locations:
//     - {name: 客厅,   x: 0.0, y: 0.0,  yaw: 0.0}
//     - {name: 餐桌旁, x: 2.5, y: 1.0,  yaw: 1.57}
//     - {name: 卧室,   x: 4.0, y: -1.0, yaw: 3.14}
//
//   x, y   ：坐标，单位米（相对于地图原点）
//   yaw    ：朝向，单位弧度（0=朝右，1.57≈朝上，3.14=朝左）
//
// 容错设计：
//   - 如果某条记录缺少字段（比如没有 yaw），跳过该记录、继续处理其他记录
//   - 如果 name 为空，跳过该记录
//   - 如果 YAML 文件不存在或格式错误，返回 false
// =============================================================================

#include "robot_nav/location_manager.hpp"

#include <yaml-cpp/yaml.h>

namespace robot_nav
{

// load_from_yaml：从 YAML 文件加载地点列表
// 参数 file_path ：YAML 文件的完整路径（例如 "/path/to/locations.yaml"）
// 返回值        ：true = 至少加载了一个有效地点，false = 加载失败
bool LocationManager::load_from_yaml(const std::string & file_path)
{
  YAML::Node root;
  try {
    // 尝试解析 YAML 文件
    root = YAML::LoadFile(file_path);
  } catch (const YAML::Exception &) {
    // 文件不存在或格式错误：返回失败
    return false;
  }

  // 获取 "locations" 列表节点
  const auto locations = root["locations"];
  if (!locations || !locations.IsSequence()) {
    // 文件里没有 "locations" 键，或者它不是列表类型
    return false;
  }

  // 清空旧数据，重新加载
  locations_.clear();

  // 遍历列表中的每一个地点条目
  for (const auto & item : locations) {
    if (!item.IsMap()) {
      // 条目不是键值对格式，跳过
      continue;
    }

    // 提取各个字段的节点
    const auto name_node = item["name"];
    const auto x_node = item["x"];
    const auto y_node = item["y"];
    const auto yaw_node = item["yaw"];

    // 任何必须字段缺失，跳过这条记录
    if (!name_node || !x_node || !y_node || !yaw_node) {
      continue;
    }

    try {
      NamedLocation loc;
      loc.name = name_node.as<std::string>();  // 地点名称（字符串）
      loc.x = x_node.as<double>();             // x 坐标（米）
      loc.y = y_node.as<double>();             // y 坐标（米）
      loc.yaw = yaw_node.as<double>();         // 朝向（弧度）

      // 名称不能为空
      if (loc.name.empty()) {
        continue;
      }

      // 以名称为 key 存入 map（重复名称会覆盖前面的记录）
      locations_[loc.name] = loc;
    } catch (const YAML::Exception &) {
      // 字段类型转换失败（例如 x 的值不是数字），跳过该记录
      continue;
    }
  }

  // 至少有一个有效地点才算成功
  return !locations_.empty();
}

// has：检查指定名称的地点是否存在
// 参数 key ：地点名称（例如 "餐桌旁"）
// 返回值   ：true = 存在，false = 不存在
bool LocationManager::has(const std::string & key) const
{
  return locations_.find(key) != locations_.end();
}

// get：获取指定名称地点的坐标信息
// 参数 key ：地点名称
// 返回值   ：NamedLocation（地点信息）；如果不存在则返回默认值（所有字段为 0）
NamedLocation LocationManager::get(const std::string & key) const
{
  auto it = locations_.find(key);
  if (it != locations_.end()) {
    return it->second;
  }
  // 不存在时返回默认构造的 NamedLocation（name="", x=0, y=0, yaw=0）
  return NamedLocation{};
}

}  // namespace robot_nav
