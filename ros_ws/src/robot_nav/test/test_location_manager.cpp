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
// 测试说明：robot_nav — 地点管理器单元测试（test_location_manager.cpp）
// =============================================================================
// 这个文件测试 LocationManager 类的 YAML 加载和地点查询功能。
//
// 测试策略：
//   - 创建临时 YAML 文件（写到 /tmp/），测试完后会被 OS 自动清理
//   - 测试正常加载、错误数据容错处理
//
// 测试用例：
//   1. LoadValidLocationsYaml      ：正常 YAML，应能加载所有有效地点
//   2. IgnoreInvalidEntryAndKeepValid：部分条目无效，应跳过无效条目保留有效的
// =============================================================================

#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "robot_nav/location_manager.hpp"

namespace
{

// 辅助函数：把字符串内容写到临时文件，返回文件路径
// suffix 用来区分不同测试的临时文件（避免冲突）
std::string write_temp_file(const std::string & content, const std::string & suffix)
{
  const std::string path = "/tmp/robot_nav_location_manager_" + suffix + ".yaml";
  std::ofstream ofs(path);
  ofs << content;
  return path;
}

}  // namespace

// 测试用例 1：加载有效的 YAML 文件
TEST(LocationManager, LoadValidLocationsYaml)
{
  // 创建临时 YAML 文件（两个有效地点）
  const auto path = write_temp_file(
    "locations:\n"
    "  - {name: 客厅, x: 0.0, y: 0.0, yaw: 0.0}\n"
    "  - {name: 厨房, x: 2.0, y: 0.5, yaw: 1.57}\n",
    "valid");

  robot_nav::LocationManager manager;
  // 加载应该成功（至少有一个有效地点）
  ASSERT_TRUE(manager.load_from_yaml(path));

  // 验证两个地点都能找到
  EXPECT_TRUE(manager.has("客厅"));
  EXPECT_TRUE(manager.has("厨房"));

  // 验证厨房的坐标是否正确
  const auto loc = manager.get("厨房");
  EXPECT_DOUBLE_EQ(loc.x, 2.0);
  EXPECT_DOUBLE_EQ(loc.y, 0.5);
}

// 测试用例 2：部分无效条目时，应跳过无效的保留有效的
// 场景：YAML 中有一个地点的 x 值不是数字（"bad" 不能转换成 double）
TEST(LocationManager, IgnoreInvalidEntryAndKeepValidOnes)
{
  // 创建临时 YAML 文件（一个有效 + 一个 x 值非法的地点）
  const auto path = write_temp_file(
    "locations:\n"
    "  - {name: 客厅, x: 0.0, y: 0.0, yaw: 0.0}\n"
    "  - {name: 无效点, x: bad, y: 1.0, yaw: 0.0}\n",  // x=bad 会触发解析错误
    "partial");

  robot_nav::LocationManager manager;
  // 加载仍应成功（客厅有效，无效点被跳过）
  ASSERT_TRUE(manager.load_from_yaml(path));

  // 验证：有效地点存在，无效地点不存在
  EXPECT_TRUE(manager.has("客厅"));
  EXPECT_FALSE(manager.has("无效点"));  // 无效条目应被跳过
}
