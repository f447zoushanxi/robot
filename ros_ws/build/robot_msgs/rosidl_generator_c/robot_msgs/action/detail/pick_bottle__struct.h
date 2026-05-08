// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_msgs:action/PickBottle.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__STRUCT_H_
#define ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'object_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_Goal
{
  rosidl_runtime_c__String object_name;
} robot_msgs__action__PickBottle_Goal;

// Struct for a sequence of robot_msgs__action__PickBottle_Goal.
typedef struct robot_msgs__action__PickBottle_Goal__Sequence
{
  robot_msgs__action__PickBottle_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_Result
{
  bool success;
  rosidl_runtime_c__String message;
} robot_msgs__action__PickBottle_Result;

// Struct for a sequence of robot_msgs__action__PickBottle_Result.
typedef struct robot_msgs__action__PickBottle_Result__Sequence
{
  robot_msgs__action__PickBottle_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stage'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_Feedback
{
  rosidl_runtime_c__String stage;
} robot_msgs__action__PickBottle_Feedback;

// Struct for a sequence of robot_msgs__action__PickBottle_Feedback.
typedef struct robot_msgs__action__PickBottle_Feedback__Sequence
{
  robot_msgs__action__PickBottle_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "robot_msgs/action/detail/pick_bottle__struct.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_msgs__action__PickBottle_Goal goal;
} robot_msgs__action__PickBottle_SendGoal_Request;

// Struct for a sequence of robot_msgs__action__PickBottle_SendGoal_Request.
typedef struct robot_msgs__action__PickBottle_SendGoal_Request__Sequence
{
  robot_msgs__action__PickBottle_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} robot_msgs__action__PickBottle_SendGoal_Response;

// Struct for a sequence of robot_msgs__action__PickBottle_SendGoal_Response.
typedef struct robot_msgs__action__PickBottle_SendGoal_Response__Sequence
{
  robot_msgs__action__PickBottle_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} robot_msgs__action__PickBottle_GetResult_Request;

// Struct for a sequence of robot_msgs__action__PickBottle_GetResult_Request.
typedef struct robot_msgs__action__PickBottle_GetResult_Request__Sequence
{
  robot_msgs__action__PickBottle_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "robot_msgs/action/detail/pick_bottle__struct.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_GetResult_Response
{
  int8_t status;
  robot_msgs__action__PickBottle_Result result;
} robot_msgs__action__PickBottle_GetResult_Response;

// Struct for a sequence of robot_msgs__action__PickBottle_GetResult_Response.
typedef struct robot_msgs__action__PickBottle_GetResult_Response__Sequence
{
  robot_msgs__action__PickBottle_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "robot_msgs/action/detail/pick_bottle__struct.h"

/// Struct defined in action/PickBottle in the package robot_msgs.
typedef struct robot_msgs__action__PickBottle_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_msgs__action__PickBottle_Feedback feedback;
} robot_msgs__action__PickBottle_FeedbackMessage;

// Struct for a sequence of robot_msgs__action__PickBottle_FeedbackMessage.
typedef struct robot_msgs__action__PickBottle_FeedbackMessage__Sequence
{
  robot_msgs__action__PickBottle_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__action__PickBottle_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_MSGS__ACTION__DETAIL__PICK_BOTTLE__STRUCT_H_
