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
// 测试说明：robot_base — 超时刹车单元测试（test_timeout_brake.cpp）
// =============================================================================
// 这个文件使用 GTest（Google Test）框架测试 apply_timeout_brake() 函数。
//
// 什么是单元测试（Unit Test）？
//   针对单个函数或类进行"白盒测试"——直接调用函数，检查输出是否符合预期。
//   优点：快（毫秒级）、不需要启动 ROS2 节点、定位问题精准。
//
// 运行方式：
//   cd ros_ws && colcon test --packages-select robot_base
//   colcon test-result --verbose
//
// 测试用例：
//   1. BrakeOnTimeout     ：超时时，速度应被清零
//   2. KeepCommandWithoutTimeout：未超时时，速度应原样保留
// =============================================================================

#include <gtest/gtest.h>

#include "robot_base/safety_utils.hpp"

// 测试用例 1：超时时刹车
// 场景：底盘超过 200ms 没收到速度指令（timeout=true），速度应被清零
TEST(BaseSafetyUtils, BrakeOnTimeout)
{
  // 构造一个非零速度指令（线速度 0.5 m/s，角速度 0.8 rad/s）
  geometry_msgs::msg::Twist input;
  input.linear.x = 0.5;
  input.angular.z = 0.8;

  // 调用被测函数，传入 timeout=true（超时）
  const auto output = robot_base::apply_timeout_brake(input, true);

  // 验证：超时后速度都应该变成 0
  EXPECT_DOUBLE_EQ(output.linear.x, 0.0);
  EXPECT_DOUBLE_EQ(output.angular.z, 0.0);
}

// 测试用例 2：未超时时保持原速
// 场景：刚收到速度指令（timeout=false），速度应原样输出
TEST(BaseSafetyUtils, KeepCommandWithoutTimeout)
{
  // 构造速度指令
  geometry_msgs::msg::Twist input;
  input.linear.x = 0.2;
  input.angular.z = -0.3;

  // 调用被测函数，传入 timeout=false（未超时）
  const auto output = robot_base::apply_timeout_brake(input, false);

  // 验证：未超时时速度应原样保留
  EXPECT_DOUBLE_EQ(output.linear.x, 0.2);
  EXPECT_DOUBLE_EQ(output.angular.z, -0.3);
}
