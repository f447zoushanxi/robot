// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_msgs:srv/FindPerson.idl
// generated code does not contain a copyright notice
#include "robot_msgs/srv/detail/find_person__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `hint_name`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_msgs__srv__FindPerson_Request__init(robot_msgs__srv__FindPerson_Request * msg)
{
  if (!msg) {
    return false;
  }
  // hint_name
  if (!rosidl_runtime_c__String__init(&msg->hint_name)) {
    robot_msgs__srv__FindPerson_Request__fini(msg);
    return false;
  }
  // timeout_sec
  return true;
}

void
robot_msgs__srv__FindPerson_Request__fini(robot_msgs__srv__FindPerson_Request * msg)
{
  if (!msg) {
    return;
  }
  // hint_name
  rosidl_runtime_c__String__fini(&msg->hint_name);
  // timeout_sec
}

bool
robot_msgs__srv__FindPerson_Request__are_equal(const robot_msgs__srv__FindPerson_Request * lhs, const robot_msgs__srv__FindPerson_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // hint_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->hint_name), &(rhs->hint_name)))
  {
    return false;
  }
  // timeout_sec
  if (lhs->timeout_sec != rhs->timeout_sec) {
    return false;
  }
  return true;
}

bool
robot_msgs__srv__FindPerson_Request__copy(
  const robot_msgs__srv__FindPerson_Request * input,
  robot_msgs__srv__FindPerson_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // hint_name
  if (!rosidl_runtime_c__String__copy(
      &(input->hint_name), &(output->hint_name)))
  {
    return false;
  }
  // timeout_sec
  output->timeout_sec = input->timeout_sec;
  return true;
}

robot_msgs__srv__FindPerson_Request *
robot_msgs__srv__FindPerson_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Request * msg = (robot_msgs__srv__FindPerson_Request *)allocator.allocate(sizeof(robot_msgs__srv__FindPerson_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__srv__FindPerson_Request));
  bool success = robot_msgs__srv__FindPerson_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__srv__FindPerson_Request__destroy(robot_msgs__srv__FindPerson_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__srv__FindPerson_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__srv__FindPerson_Request__Sequence__init(robot_msgs__srv__FindPerson_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Request * data = NULL;

  if (size) {
    data = (robot_msgs__srv__FindPerson_Request *)allocator.zero_allocate(size, sizeof(robot_msgs__srv__FindPerson_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__srv__FindPerson_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__srv__FindPerson_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_msgs__srv__FindPerson_Request__Sequence__fini(robot_msgs__srv__FindPerson_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_msgs__srv__FindPerson_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_msgs__srv__FindPerson_Request__Sequence *
robot_msgs__srv__FindPerson_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Request__Sequence * array = (robot_msgs__srv__FindPerson_Request__Sequence *)allocator.allocate(sizeof(robot_msgs__srv__FindPerson_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__srv__FindPerson_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__srv__FindPerson_Request__Sequence__destroy(robot_msgs__srv__FindPerson_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__srv__FindPerson_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__srv__FindPerson_Request__Sequence__are_equal(const robot_msgs__srv__FindPerson_Request__Sequence * lhs, const robot_msgs__srv__FindPerson_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__srv__FindPerson_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__srv__FindPerson_Request__Sequence__copy(
  const robot_msgs__srv__FindPerson_Request__Sequence * input,
  robot_msgs__srv__FindPerson_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__srv__FindPerson_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_msgs__srv__FindPerson_Request * data =
      (robot_msgs__srv__FindPerson_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__srv__FindPerson_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_msgs__srv__FindPerson_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_msgs__srv__FindPerson_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `identity`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
robot_msgs__srv__FindPerson_Response__init(robot_msgs__srv__FindPerson_Response * msg)
{
  if (!msg) {
    return false;
  }
  // found
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    robot_msgs__srv__FindPerson_Response__fini(msg);
    return false;
  }
  // confidence
  // identity
  if (!rosidl_runtime_c__String__init(&msg->identity)) {
    robot_msgs__srv__FindPerson_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    robot_msgs__srv__FindPerson_Response__fini(msg);
    return false;
  }
  return true;
}

void
robot_msgs__srv__FindPerson_Response__fini(robot_msgs__srv__FindPerson_Response * msg)
{
  if (!msg) {
    return;
  }
  // found
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // confidence
  // identity
  rosidl_runtime_c__String__fini(&msg->identity);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
robot_msgs__srv__FindPerson_Response__are_equal(const robot_msgs__srv__FindPerson_Response * lhs, const robot_msgs__srv__FindPerson_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // found
  if (lhs->found != rhs->found) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // identity
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->identity), &(rhs->identity)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
robot_msgs__srv__FindPerson_Response__copy(
  const robot_msgs__srv__FindPerson_Response * input,
  robot_msgs__srv__FindPerson_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // found
  output->found = input->found;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // identity
  if (!rosidl_runtime_c__String__copy(
      &(input->identity), &(output->identity)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

robot_msgs__srv__FindPerson_Response *
robot_msgs__srv__FindPerson_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Response * msg = (robot_msgs__srv__FindPerson_Response *)allocator.allocate(sizeof(robot_msgs__srv__FindPerson_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__srv__FindPerson_Response));
  bool success = robot_msgs__srv__FindPerson_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__srv__FindPerson_Response__destroy(robot_msgs__srv__FindPerson_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__srv__FindPerson_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__srv__FindPerson_Response__Sequence__init(robot_msgs__srv__FindPerson_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Response * data = NULL;

  if (size) {
    data = (robot_msgs__srv__FindPerson_Response *)allocator.zero_allocate(size, sizeof(robot_msgs__srv__FindPerson_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__srv__FindPerson_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__srv__FindPerson_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_msgs__srv__FindPerson_Response__Sequence__fini(robot_msgs__srv__FindPerson_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_msgs__srv__FindPerson_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_msgs__srv__FindPerson_Response__Sequence *
robot_msgs__srv__FindPerson_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__FindPerson_Response__Sequence * array = (robot_msgs__srv__FindPerson_Response__Sequence *)allocator.allocate(sizeof(robot_msgs__srv__FindPerson_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__srv__FindPerson_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__srv__FindPerson_Response__Sequence__destroy(robot_msgs__srv__FindPerson_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__srv__FindPerson_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__srv__FindPerson_Response__Sequence__are_equal(const robot_msgs__srv__FindPerson_Response__Sequence * lhs, const robot_msgs__srv__FindPerson_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__srv__FindPerson_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__srv__FindPerson_Response__Sequence__copy(
  const robot_msgs__srv__FindPerson_Response__Sequence * input,
  robot_msgs__srv__FindPerson_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__srv__FindPerson_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_msgs__srv__FindPerson_Response * data =
      (robot_msgs__srv__FindPerson_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__srv__FindPerson_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_msgs__srv__FindPerson_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_msgs__srv__FindPerson_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
