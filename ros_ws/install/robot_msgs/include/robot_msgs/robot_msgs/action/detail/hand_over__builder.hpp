// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_msgs:action/HandOver.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__ACTION__DETAIL__HAND_OVER__BUILDER_HPP_
#define ROBOT_MSGS__ACTION__DETAIL__HAND_OVER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_msgs/action/detail/hand_over__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_Goal_target_identity
{
public:
  Init_HandOver_Goal_target_identity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::HandOver_Goal target_identity(::robot_msgs::action::HandOver_Goal::_target_identity_type arg)
  {
    msg_.target_identity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_Goal>()
{
  return robot_msgs::action::builder::Init_HandOver_Goal_target_identity();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_Result_message
{
public:
  explicit Init_HandOver_Result_message(::robot_msgs::action::HandOver_Result & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::HandOver_Result message(::robot_msgs::action::HandOver_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_Result msg_;
};

class Init_HandOver_Result_success
{
public:
  Init_HandOver_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandOver_Result_message success(::robot_msgs::action::HandOver_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_HandOver_Result_message(msg_);
  }

private:
  ::robot_msgs::action::HandOver_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_Result>()
{
  return robot_msgs::action::builder::Init_HandOver_Result_success();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_Feedback_stage
{
public:
  Init_HandOver_Feedback_stage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::HandOver_Feedback stage(::robot_msgs::action::HandOver_Feedback::_stage_type arg)
  {
    msg_.stage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_Feedback>()
{
  return robot_msgs::action::builder::Init_HandOver_Feedback_stage();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_SendGoal_Request_goal
{
public:
  explicit Init_HandOver_SendGoal_Request_goal(::robot_msgs::action::HandOver_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::HandOver_SendGoal_Request goal(::robot_msgs::action::HandOver_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_SendGoal_Request msg_;
};

class Init_HandOver_SendGoal_Request_goal_id
{
public:
  Init_HandOver_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandOver_SendGoal_Request_goal goal_id(::robot_msgs::action::HandOver_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_HandOver_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_msgs::action::HandOver_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_SendGoal_Request>()
{
  return robot_msgs::action::builder::Init_HandOver_SendGoal_Request_goal_id();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_SendGoal_Response_stamp
{
public:
  explicit Init_HandOver_SendGoal_Response_stamp(::robot_msgs::action::HandOver_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::HandOver_SendGoal_Response stamp(::robot_msgs::action::HandOver_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_SendGoal_Response msg_;
};

class Init_HandOver_SendGoal_Response_accepted
{
public:
  Init_HandOver_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandOver_SendGoal_Response_stamp accepted(::robot_msgs::action::HandOver_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_HandOver_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_msgs::action::HandOver_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_SendGoal_Response>()
{
  return robot_msgs::action::builder::Init_HandOver_SendGoal_Response_accepted();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_GetResult_Request_goal_id
{
public:
  Init_HandOver_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_msgs::action::HandOver_GetResult_Request goal_id(::robot_msgs::action::HandOver_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_GetResult_Request>()
{
  return robot_msgs::action::builder::Init_HandOver_GetResult_Request_goal_id();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_GetResult_Response_result
{
public:
  explicit Init_HandOver_GetResult_Response_result(::robot_msgs::action::HandOver_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::HandOver_GetResult_Response result(::robot_msgs::action::HandOver_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_GetResult_Response msg_;
};

class Init_HandOver_GetResult_Response_status
{
public:
  Init_HandOver_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandOver_GetResult_Response_result status(::robot_msgs::action::HandOver_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_HandOver_GetResult_Response_result(msg_);
  }

private:
  ::robot_msgs::action::HandOver_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_GetResult_Response>()
{
  return robot_msgs::action::builder::Init_HandOver_GetResult_Response_status();
}

}  // namespace robot_msgs


namespace robot_msgs
{

namespace action
{

namespace builder
{

class Init_HandOver_FeedbackMessage_feedback
{
public:
  explicit Init_HandOver_FeedbackMessage_feedback(::robot_msgs::action::HandOver_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_msgs::action::HandOver_FeedbackMessage feedback(::robot_msgs::action::HandOver_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_msgs::action::HandOver_FeedbackMessage msg_;
};

class Init_HandOver_FeedbackMessage_goal_id
{
public:
  Init_HandOver_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandOver_FeedbackMessage_feedback goal_id(::robot_msgs::action::HandOver_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_HandOver_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_msgs::action::HandOver_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_msgs::action::HandOver_FeedbackMessage>()
{
  return robot_msgs::action::builder::Init_HandOver_FeedbackMessage_goal_id();
}

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__ACTION__DETAIL__HAND_OVER__BUILDER_HPP_
