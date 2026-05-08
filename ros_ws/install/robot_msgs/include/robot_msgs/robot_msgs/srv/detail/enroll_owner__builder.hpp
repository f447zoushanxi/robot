// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:srv/EnrollOwner.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__BUILDER_HPP_
#define ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_msgs/srv/detail/enroll_owner__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_EnrollOwner_Request_window_sec
{
public:
  explicit Init_EnrollOwner_Request_window_sec(::robot_msgs::srv::EnrollOwner_Request & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::EnrollOwner_Request window_sec(::robot_msgs::srv::EnrollOwner_Request::_window_sec_type arg)
  {
    msg_.window_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::EnrollOwner_Request msg_;
};

class Init_EnrollOwner_Request_require_physical_confirm
{
public:
  Init_EnrollOwner_Request_require_physical_confirm()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EnrollOwner_Request_window_sec require_physical_confirm(::robot_msgs::srv::EnrollOwner_Request::_require_physical_confirm_type arg)
  {
    msg_.require_physical_confirm = std::move(arg);
    return Init_EnrollOwner_Request_window_sec(msg_);
  }

private:
  ::robot_msgs::srv::EnrollOwner_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::EnrollOwner_Request>()
{
  return robot_msgs::srv::builder::Init_EnrollOwner_Request_require_physical_confirm();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_EnrollOwner_Response_message
{
public:
  explicit Init_EnrollOwner_Response_message(::robot_msgs::srv::EnrollOwner_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::EnrollOwner_Response message(::robot_msgs::srv::EnrollOwner_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::EnrollOwner_Response msg_;
};

class Init_EnrollOwner_Response_owner_id
{
public:
  explicit Init_EnrollOwner_Response_owner_id(::robot_msgs::srv::EnrollOwner_Response & msg)
  : msg_(msg)
  {}
  Init_EnrollOwner_Response_message owner_id(::robot_msgs::srv::EnrollOwner_Response::_owner_id_type arg)
  {
    msg_.owner_id = std::move(arg);
    return Init_EnrollOwner_Response_message(msg_);
  }

private:
  ::robot_msgs::srv::EnrollOwner_Response msg_;
};

class Init_EnrollOwner_Response_accepted
{
public:
  Init_EnrollOwner_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EnrollOwner_Response_owner_id accepted(::robot_msgs::srv::EnrollOwner_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_EnrollOwner_Response_owner_id(msg_);
  }

private:
  ::robot_msgs::srv::EnrollOwner_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::EnrollOwner_Response>()
{
  return robot_msgs::srv::builder::Init_EnrollOwner_Response_accepted();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__BUILDER_HPP_
