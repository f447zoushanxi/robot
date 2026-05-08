// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_msgs:srv/EnrollOwner.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__TRAITS_HPP_
#define ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_msgs/srv/detail/enroll_owner__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EnrollOwner_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: require_physical_confirm
  {
    out << "require_physical_confirm: ";
    rosidl_generator_traits::value_to_yaml(msg.require_physical_confirm, out);
    out << ", ";
  }

  // member: window_sec
  {
    out << "window_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.window_sec, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EnrollOwner_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: require_physical_confirm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "require_physical_confirm: ";
    rosidl_generator_traits::value_to_yaml(msg.require_physical_confirm, out);
    out << "\n";
  }

  // member: window_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "window_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.window_sec, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EnrollOwner_Request & msg, bool use_flow_style = false)
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
  const robot_msgs::srv::EnrollOwner_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_msgs::srv::EnrollOwner_Request & msg)
{
  return robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_msgs::srv::EnrollOwner_Request>()
{
  return "robot_msgs::srv::EnrollOwner_Request";
}

template<>
inline const char * name<robot_msgs::srv::EnrollOwner_Request>()
{
  return "robot_msgs/srv/EnrollOwner_Request";
}

template<>
struct has_fixed_size<robot_msgs::srv::EnrollOwner_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_msgs::srv::EnrollOwner_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_msgs::srv::EnrollOwner_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EnrollOwner_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: owner_id
  {
    out << "owner_id: ";
    rosidl_generator_traits::value_to_yaml(msg.owner_id, out);
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
  const EnrollOwner_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: owner_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "owner_id: ";
    rosidl_generator_traits::value_to_yaml(msg.owner_id, out);
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

inline std::string to_yaml(const EnrollOwner_Response & msg, bool use_flow_style = false)
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
  const robot_msgs::srv::EnrollOwner_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_msgs::srv::EnrollOwner_Response & msg)
{
  return robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_msgs::srv::EnrollOwner_Response>()
{
  return "robot_msgs::srv::EnrollOwner_Response";
}

template<>
inline const char * name<robot_msgs::srv::EnrollOwner_Response>()
{
  return "robot_msgs/srv/EnrollOwner_Response";
}

template<>
struct has_fixed_size<robot_msgs::srv::EnrollOwner_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_msgs::srv::EnrollOwner_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_msgs::srv::EnrollOwner_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_msgs::srv::EnrollOwner>()
{
  return "robot_msgs::srv::EnrollOwner";
}

template<>
inline const char * name<robot_msgs::srv::EnrollOwner>()
{
  return "robot_msgs/srv/EnrollOwner";
}

template<>
struct has_fixed_size<robot_msgs::srv::EnrollOwner>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_msgs::srv::EnrollOwner_Request>::value &&
    has_fixed_size<robot_msgs::srv::EnrollOwner_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_msgs::srv::EnrollOwner>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_msgs::srv::EnrollOwner_Request>::value &&
    has_bounded_size<robot_msgs::srv::EnrollOwner_Response>::value
  >
{
};

template<>
struct is_service<robot_msgs::srv::EnrollOwner>
  : std::true_type
{
};

template<>
struct is_service_request<robot_msgs::srv::EnrollOwner_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_msgs::srv::EnrollOwner_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__TRAITS_HPP_
