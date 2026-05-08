// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_msgs:srv/FindPerson.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__TRAITS_HPP_
#define ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_msgs/srv/detail/find_person__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const FindPerson_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: hint_name
  {
    out << "hint_name: ";
    rosidl_generator_traits::value_to_yaml(msg.hint_name, out);
    out << ", ";
  }

  // member: timeout_sec
  {
    out << "timeout_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_sec, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FindPerson_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: hint_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hint_name: ";
    rosidl_generator_traits::value_to_yaml(msg.hint_name, out);
    out << "\n";
  }

  // member: timeout_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timeout_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_sec, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FindPerson_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_msgs::srv::FindPerson_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_msgs::srv::FindPerson_Request & msg)
{
  return robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_msgs::srv::FindPerson_Request>()
{
  return "robot_msgs::srv::FindPerson_Request";
}

template<>
inline const char * name<robot_msgs::srv::FindPerson_Request>()
{
  return "robot_msgs/srv/FindPerson_Request";
}

template<>
struct has_fixed_size<robot_msgs::srv::FindPerson_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_msgs::srv::FindPerson_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_msgs::srv::FindPerson_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const FindPerson_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: found
  {
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: identity
  {
    out << "identity: ";
    rosidl_generator_traits::value_to_yaml(msg.identity, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FindPerson_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: found
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: identity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "identity: ";
    rosidl_generator_traits::value_to_yaml(msg.identity, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FindPerson_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_msgs::srv::FindPerson_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_msgs::srv::FindPerson_Response & msg)
{
  return robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_msgs::srv::FindPerson_Response>()
{
  return "robot_msgs::srv::FindPerson_Response";
}

template<>
inline const char * name<robot_msgs::srv::FindPerson_Response>()
{
  return "robot_msgs/srv/FindPerson_Response";
}

template<>
struct has_fixed_size<robot_msgs::srv::FindPerson_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_msgs::srv::FindPerson_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_msgs::srv::FindPerson_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_msgs::srv::FindPerson>()
{
  return "robot_msgs::srv::FindPerson";
}

template<>
inline const char * name<robot_msgs::srv::FindPerson>()
{
  return "robot_msgs/srv/FindPerson";
}

template<>
struct has_fixed_size<robot_msgs::srv::FindPerson>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_msgs::srv::FindPerson_Request>::value &&
    has_fixed_size<robot_msgs::srv::FindPerson_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_msgs::srv::FindPerson>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_msgs::srv::FindPerson_Request>::value &&
    has_bounded_size<robot_msgs::srv::FindPerson_Response>::value
  >
{
};

template<>
struct is_service<robot_msgs::srv::FindPerson>
  : std::true_type
{
};

template<>
struct is_service_request<robot_msgs::srv::FindPerson_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_msgs::srv::FindPerson_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__TRAITS_HPP_
