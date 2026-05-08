// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:action/PickBottle.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__BUILDER_HPP_
#define ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_msgs/action/detail/pick_bottle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_Goal_object_name
{
public:
  Init_PickBottle_Goal_object_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::PickBottle_Goal object_name(::robot_msgs::action::PickBottle_Goal::_object_name_type arg)
  {
    msg_.object_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_Goal>()
{
  return robot_msgs::action::builder::Init_PickBottle_Goal_object_name();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_Result_message
{
public:
  explicit Init_PickBottle_Result_message(::robot_msgs::action::PickBottle_Result & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::PickBottle_Result message(::robot_msgs::action::PickBottle_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_Result msg_;
};

class Init_PickBottle_Result_success
{
public:
  Init_PickBottle_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PickBottle_Result_message success(::robot_msgs::action::PickBottle_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_PickBottle_Result_message(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_Result>()
{
  return robot_msgs::action::builder::Init_PickBottle_Result_success();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_Feedback_stage
{
public:
  Init_PickBottle_Feedback_stage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::PickBottle_Feedback stage(::robot_msgs::action::PickBottle_Feedback::_stage_type arg)
  {
    msg_.stage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_Feedback>()
{
  return robot_msgs::action::builder::Init_PickBottle_Feedback_stage();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_SendGoal_Request_goal
{
public:
  explicit Init_PickBottle_SendGoal_Request_goal(::robot_msgs::action::PickBottle_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::PickBottle_SendGoal_Request goal(::robot_msgs::action::PickBottle_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_SendGoal_Request msg_;
};

class Init_PickBottle_SendGoal_Request_goal_id
{
public:
  Init_PickBottle_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PickBottle_SendGoal_Request_goal goal_id(::robot_msgs::action::PickBottle_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PickBottle_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_SendGoal_Request>()
{
  return robot_msgs::action::builder::Init_PickBottle_SendGoal_Request_goal_id();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_SendGoal_Response_stamp
{
public:
  explicit Init_PickBottle_SendGoal_Response_stamp(::robot_msgs::action::PickBottle_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::PickBottle_SendGoal_Response stamp(::robot_msgs::action::PickBottle_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_SendGoal_Response msg_;
};

class Init_PickBottle_SendGoal_Response_accepted
{
public:
  Init_PickBottle_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PickBottle_SendGoal_Response_stamp accepted(::robot_msgs::action::PickBottle_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_PickBottle_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_SendGoal_Response>()
{
  return robot_msgs::action::builder::Init_PickBottle_SendGoal_Response_accepted();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_GetResult_Request_goal_id
{
public:
  Init_PickBottle_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::PickBottle_GetResult_Request goal_id(::robot_msgs::action::PickBottle_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_GetResult_Request>()
{
  return robot_msgs::action::builder::Init_PickBottle_GetResult_Request_goal_id();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_GetResult_Response_result
{
public:
  explicit Init_PickBottle_GetResult_Response_result(::robot_msgs::action::PickBottle_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::PickBottle_GetResult_Response result(::robot_msgs::action::PickBottle_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_GetResult_Response msg_;
};

class Init_PickBottle_GetResult_Response_status
{
public:
  Init_PickBottle_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PickBottle_GetResult_Response_result status(::robot_msgs::action::PickBottle_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_PickBottle_GetResult_Response_result(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_GetResult_Response>()
{
  return robot_msgs::action::builder::Init_PickBottle_GetResult_Response_status();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_PickBottle_FeedbackMessage_feedback
{
public:
  explicit Init_PickBottle_FeedbackMessage_feedback(::robot_msgs::action::PickBottle_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::PickBottle_FeedbackMessage feedback(::robot_msgs::action::PickBottle_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_FeedbackMessage msg_;
};

class Init_PickBottle_FeedbackMessage_goal_id
{
public:
  Init_PickBottle_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PickBottle_FeedbackMessage_feedback goal_id(::robot_msgs::action::PickBottle_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PickBottle_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_msgs::action::PickBottle_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::PickBottle_FeedbackMessage>()
{
  return robot_msgs::action::builder::Init_PickBottle_FeedbackMessage_goal_id();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__BUILDER_HPP_
