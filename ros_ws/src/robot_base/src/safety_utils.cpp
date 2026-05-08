#include "robot_base/safety_utils.hpp"

namespace robot_base
{

geometry_msgs::msg::Twist apply_timeout_brake(const geometry_msgs::msg::Twist & input, bool timeout)
{
  auto output = input;
  if (timeout) {
    output.linear.x = 0.0;
    output.angular.z = 0.0;
  }
  return output;
}

}  // namespace robot_base
