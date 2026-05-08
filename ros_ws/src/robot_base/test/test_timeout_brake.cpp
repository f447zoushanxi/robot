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

#include <gtest/gtest.h>

#include "robot_base/safety_utils.hpp"

TEST(BaseSafetyUtils, BrakeOnTimeout)
{
  geometry_msgs::msg::Twist input;
  input.linear.x = 0.5;
  input.angular.z = 0.8;

  const auto output = robot_base::apply_timeout_brake(input, true);
  EXPECT_DOUBLE_EQ(output.linear.x, 0.0);
  EXPECT_DOUBLE_EQ(output.angular.z, 0.0);
}

TEST(BaseSafetyUtils, KeepCommandWithoutTimeout)
{
  geometry_msgs::msg::Twist input;
  input.linear.x = 0.2;
  input.angular.z = -0.3;

  const auto output = robot_base::apply_timeout_brake(input, false);
  EXPECT_DOUBLE_EQ(output.linear.x, 0.2);
  EXPECT_DOUBLE_EQ(output.angular.z, -0.3);
}
