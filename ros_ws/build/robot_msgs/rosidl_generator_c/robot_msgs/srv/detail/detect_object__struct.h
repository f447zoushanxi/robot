// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_msgs:srv/DetectObject.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__STRUCT_H_
#define ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__STRUCT_H_

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

/// Struct defined in srv/DetectObject in the package robot_msgs.
typedef struct robot_msgs__srv__DetectObject_Request
{
  rosidl_runtime_c__String object_name;
  /// 服务调用超时（秒）
  float timeout_sec;
} robot_msgs__srv__DetectObject_Request;

// Struct for a sequence of robot_msgs__srv__DetectObject_Request.
typedef struct robot_msgs__srv__DetectObject_Request__Sequence
{
  robot_msgs__srv__DetectObject_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__srv__DetectObject_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'frame_id'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/DetectObject in the package robot_msgs.
typedef struct robot_msgs__srv__DetectObject_Response
{
  bool found;
  /// 目标在 base_link 坐标系下的 3D 位置
  geometry_msgs__msg__Point position;
  /// 检测置信度 [0,1]
  float confidence;
  /// 输出坐标系名称
  rosidl_runtime_c__String frame_id;
  /// 额外调试信息
  rosidl_runtime_c__String message;
} robot_msgs__srv__DetectObject_Response;

// Struct for a sequence of robot_msgs__srv__DetectObject_Response.
typedef struct robot_msgs__srv__DetectObject_Response__Sequence
{
  robot_msgs__srv__DetectObject_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_msgs__srv__DetectObject_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_MSGS__SRV__DETAIL__DETECT_OBJECT__STRUCT_H_
