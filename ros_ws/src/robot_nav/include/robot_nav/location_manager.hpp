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
// 模块说明：robot_nav — 地点管理器声明（location_manager.hpp）
// =============================================================================
// 这个头文件定义了地点数据结构（NamedLocation）和地点管理器类（LocationManager）。
//
// 使用场景：
//   nav_server_node 启动时调用 load_from_yaml() 加载 locations.yaml，
//   然后通过 has() 和 get() 查找特定地点的坐标。
// =============================================================================

#pragma once

#include <map>
#include <string>

namespace robot_nav
{

// NamedLocation：带名称的地点（二维坐标 + 朝向）
// name ：地点名称，例如"餐桌旁"、"客厅"
// x    ：横坐标（单位：米），相对于地图原点
// y    ：纵坐标（单位：米），相对于地图原点
// yaw  ：机器人到达该地点时的朝向（单位：弧度，0=朝右，1.57≈朝上）
struct NamedLocation
{
  std::string name;
  double x{0.0};
  double y{0.0};
  double yaw{0.0};
};

// LocationManager：地点管理器
// 负责加载、存储、查询家庭地点列表
class LocationManager
{
public:
  // load_from_yaml：从 YAML 文件加载地点列表
  // 返回 true 表示至少加载了一个有效地点
  bool load_from_yaml(const std::string & file_path);

  // has：检查指定名称的地点是否存在
  bool has(const std::string & key) const;

  // get：获取指定名称的地点信息（不存在时返回默认值）
  NamedLocation get(const std::string & key) const;

private:
  // 内部存储：以地点名称为 key 的 map（字典）
  std::map<std::string, NamedLocation> locations_;
};

}  // namespace robot_nav
