#pragma once

#include "geometry_msgs/msg/twist.hpp"

namespace robot_base
{

geometry_msgs::msg::Twist apply_timeout_brake(
  const geometry_msgs::msg::Twist & input,
  bool timeout);

}  // namespace robot_base
