// Copyright (c) 2026.
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

#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "robot_nav/location_manager.hpp"

namespace
{

std::string write_temp_file(const std::string & content, const std::string & suffix)
{
  const std::string path = "/tmp/robot_nav_location_manager_" + suffix + ".yaml";
  std::ofstream ofs(path);
  ofs << content;
  return path;
}

}  // namespace

TEST(LocationManager, LoadValidLocationsYaml)
{
  const auto path = write_temp_file(
    "locations:\n"
    "  - {name: 客厅, x: 0.0, y: 0.0, yaw: 0.0}\n"
    "  - {name: 厨房, x: 2.0, y: 0.5, yaw: 1.57}\n",
    "valid");

  robot_nav::LocationManager manager;
  ASSERT_TRUE(manager.load_from_yaml(path));
  EXPECT_TRUE(manager.has("客厅"));
  EXPECT_TRUE(manager.has("厨房"));
  const auto loc = manager.get("厨房");
  EXPECT_DOUBLE_EQ(loc.x, 2.0);
  EXPECT_DOUBLE_EQ(loc.y, 0.5);
}

TEST(LocationManager, IgnoreInvalidEntryAndKeepValidOnes)
{
  const auto path = write_temp_file(
    "locations:\n"
    "  - {name: 客厅, x: 0.0, y: 0.0, yaw: 0.0}\n"
    "  - {name: 无效点, x: bad, y: 1.0, yaw: 0.0}\n",
    "partial");

  robot_nav::LocationManager manager;
  ASSERT_TRUE(manager.load_from_yaml(path));
  EXPECT_TRUE(manager.has("客厅"));
  EXPECT_FALSE(manager.has("无效点"));
}
