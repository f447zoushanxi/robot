// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:srv/DetectObject.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__BUILDER_HPP_
#define ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_msgs/srv/detail/detect_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_DetectObject_Request_timeout_sec
{
public:
  explicit Init_DetectObject_Request_timeout_sec(::robot_msgs::srv::DetectObject_Request & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::DetectObject_Request timeout_sec(::robot_msgs::srv::DetectObject_Request::_timeout_sec_type arg)
  {
    msg_.timeout_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Request msg_;
};

class Init_DetectObject_Request_object_name
{
public:
  Init_DetectObject_Request_object_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectObject_Request_timeout_sec object_name(::robot_msgs::srv::DetectObject_Request::_object_name_type arg)
  {
    msg_.object_name = std::move(arg);
    return Init_DetectObject_Request_timeout_sec(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::DetectObject_Request>()
{
  return robot_msgs::srv::builder::Init_DetectObject_Request_object_name();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace srv
{

namespace builder
{

class Init_DetectObject_Response_message
{
public:
  explicit Init_DetectObject_Response_message(::robot_msgs::srv::DetectObject_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::srv::DetectObject_Response message(::robot_msgs::srv::DetectObject_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Response msg_;
};

class Init_DetectObject_Response_frame_id
{
public:
  explicit Init_DetectObject_Response_frame_id(::robot_msgs::srv::DetectObject_Response & msg)
  : msg_(msg)
  {}
  Init_DetectObject_Response_message frame_id(::robot_msgs::srv::DetectObject_Response::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_DetectObject_Response_message(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Response msg_;
};

class Init_DetectObject_Response_confidence
{
public:
  explicit Init_DetectObject_Response_confidence(::robot_msgs::srv::DetectObject_Response & msg)
  : msg_(msg)
  {}
  Init_DetectObject_Response_frame_id confidence(::robot_msgs::srv::DetectObject_Response::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_DetectObject_Response_frame_id(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Response msg_;
};

class Init_DetectObject_Response_position
{
public:
  explicit Init_DetectObject_Response_position(::robot_msgs::srv::DetectObject_Response & msg)
  : msg_(msg)
  {}
  Init_DetectObject_Response_confidence position(::robot_msgs::srv::DetectObject_Response::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_DetectObject_Response_confidence(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Response msg_;
};

class Init_DetectObject_Response_found
{
public:
  Init_DetectObject_Response_found()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectObject_Response_position found(::robot_msgs::srv::DetectObject_Response::_found_type arg)
  {
    msg_.found = std::move(arg);
    return Init_DetectObject_Response_position(msg_);
  }

private:
  ::robot_msgs::srv::DetectObject_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::srv::DetectObject_Response>()
{
  return robot_msgs::srv::builder::Init_DetectObject_Response_found();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__BUILDER_HPP_
