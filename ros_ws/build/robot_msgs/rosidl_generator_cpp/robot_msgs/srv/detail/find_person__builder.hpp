// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:srv/FindPerson.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__BUILDER_HPP_
#define ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_msgs/srv/detail/find_person__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_FindPerson_Request_timeout_sec
{
public:
  explicit Init_FindPerson_Request_timeout_sec(::robot_msgs::srv::FindPerson_Request & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::FindPerson_Request timeout_sec(::robot_msgs::srv::FindPerson_Request::_timeout_sec_type arg)
  {
    msg_.timeout_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Request msg_;
};

class Init_FindPerson_Request_hint_name
{
public:
  Init_FindPerson_Request_hint_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FindPerson_Request_timeout_sec hint_name(::robot_msgs::srv::FindPerson_Request::_hint_name_type arg)
  {
    msg_.hint_name = std::move(arg);
    return Init_FindPerson_Request_timeout_sec(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::FindPerson_Request>()
{
  return robot_msgs::srv::builder::Init_FindPerson_Request_hint_name();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_FindPerson_Response_message
{
public:
  explicit Init_FindPerson_Response_message(::robot_msgs::srv::FindPerson_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::FindPerson_Response message(::robot_msgs::srv::FindPerson_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Response msg_;
};

class Init_FindPerson_Response_identity
{
public:
  explicit Init_FindPerson_Response_identity(::robot_msgs::srv::FindPerson_Response & msg)
  : msg_(msg)
  {}
  Init_FindPerson_Response_message identity(::robot_msgs::srv::FindPerson_Response::_identity_type arg)
  {
    msg_.identity = std::move(arg);
    return Init_FindPerson_Response_message(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Response msg_;
};

class Init_FindPerson_Response_confidence
{
public:
  explicit Init_FindPerson_Response_confidence(::robot_msgs::srv::FindPerson_Response & msg)
  : msg_(msg)
  {}
  Init_FindPerson_Response_identity confidence(::robot_msgs::srv::FindPerson_Response::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_FindPerson_Response_identity(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Response msg_;
};

class Init_FindPerson_Response_position
{
public:
  explicit Init_FindPerson_Response_position(::robot_msgs::srv::FindPerson_Response & msg)
  : msg_(msg)
  {}
  Init_FindPerson_Response_confidence position(::robot_msgs::srv::FindPerson_Response::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_FindPerson_Response_confidence(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Response msg_;
};

class Init_FindPerson_Response_found
{
public:
  Init_FindPerson_Response_found()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FindPerson_Response_position found(::robot_msgs::srv::FindPerson_Response::_found_type arg)
  {
    msg_.found = std::move(arg);
    return Init_FindPerson_Response_position(msg_);
  }

private:
  ::robot_msgs::srv::FindPerson_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::FindPerson_Response>()
{
  return robot_msgs::srv::builder::Init_FindPerson_Response_found();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__BUILDER_HPP_
