// Copyright (c) 2026.
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
