// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_msgs:srv/EnrollOwner.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_H_
#define ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/EnrollOwner in the package robot_msgs.
typedef struct robot_msgs__srv__EnrollOwner_Request
{
  bool require_physical_confirm;
  /// 物理确认窗口时长（秒）
  float window_sec;
} robot_msgs__srv__EnrollOwner_Request;

// Struct for a sequence of robot_msgs__srv__EnrollOwner_Request.
typedef struct robot_msgs__srv__EnrollOwner_Request__Sequence
{
  robot_msgs__srv__EnrollOwner_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__srv__EnrollOwner_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'owner_id'
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/EnrollOwner in the package robot_msgs.
typedef struct robot_msgs__srv__EnrollOwner_Response
{
  bool accepted;
  /// owner id（成功时返回）
  rosidl_runtime_c__String owner_id;
  /// 结果说明
  rosidl_runtime_c__String message;
} robot_msgs__srv__EnrollOwner_Response;

// Struct for a sequence of robot_msgs__srv__EnrollOwner_Response.
typedef struct robot_msgs__srv__EnrollOwner_Response__Sequence
{
  robot_msgs__srv__EnrollOwner_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__srv__EnrollOwner_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_H_
