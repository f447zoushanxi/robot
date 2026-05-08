// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_msgs:srv/EnrollOwner.idl
// generated code does not contain a copyright notice
#include "robot_msgs/srv/detail/enroll_owner__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
robot_msgs__srv__EnrollOwner_Request__init(robot_msgs__srv__EnrollOwner_Request * msg)
{
  if (!msg) {
    return false;
  }
  // require_physical_confirm
  // window_sec
  return true;
}

void
robot_msgs__srv__EnrollOwner_Request__fini(robot_msgs__srv__EnrollOwner_Request * msg)
{
  if (!msg) {
    return;
  }
  // require_physical_confirm
  // window_sec
}

bool
robot_msgs__srv__EnrollOwner_Request__are_equal(const robot_msgs__srv__EnrollOwner_Request * lhs, const robot_msgs__srv__EnrollOwner_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // require_physical_confirm
  if (lhs->require_physical_confirm != rhs->require_physical_confirm) {
    return false;
  }
  // window_sec
  if (lhs->window_sec != rhs->window_sec) {
    return false;
  }
  return true;
}

bool
robot_msgs__srv__EnrollOwner_Request__copy(
  const robot_msgs__srv__EnrollOwner_Request * input,
  robot_msgs__srv__EnrollOwner_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // require_physical_confirm
  output->require_physical_confirm = input->require_physical_confirm;
  // window_sec
  output->window_sec = input->window_sec;
  return true;
}

robot_msgs__srv__EnrollOwner_Request *
robot_msgs__srv__EnrollOwner_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Request * msg = (robot_msgs__srv__EnrollOwner_Request *)allocator.allocate(sizeof(robot_msgs__srv__EnrollOwner_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__srv__EnrollOwner_Request));
  bool success = robot_msgs__srv__EnrollOwner_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__srv__EnrollOwner_Request__destroy(robot_msgs__srv__EnrollOwner_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__srv__EnrollOwner_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__srv__EnrollOwner_Request__Sequence__init(robot_msgs__srv__EnrollOwner_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Request * data = NULL;

  if (size) {
    data = (robot_msgs__srv__EnrollOwner_Request *)allocator.zero_allocate(size, sizeof(robot_msgs__srv__EnrollOwner_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__srv__EnrollOwner_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__srv__EnrollOwner_Request__fini(&data[i - 1]);
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
robot_msgs__srv__EnrollOwner_Request__Sequence__fini(robot_msgs__srv__EnrollOwner_Request__Sequence * array)
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
      robot_msgs__srv__EnrollOwner_Request__fini(&array->data[i]);
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

robot_msgs__srv__EnrollOwner_Request__Sequence *
robot_msgs__srv__EnrollOwner_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Request__Sequence * array = (robot_msgs__srv__EnrollOwner_Request__Sequence *)allocator.allocate(sizeof(robot_msgs__srv__EnrollOwner_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__srv__EnrollOwner_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__srv__EnrollOwner_Request__Sequence__destroy(robot_msgs__srv__EnrollOwner_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__srv__EnrollOwner_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__srv__EnrollOwner_Request__Sequence__are_equal(const robot_msgs__srv__EnrollOwner_Request__Sequence * lhs, const robot_msgs__srv__EnrollOwner_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__srv__EnrollOwner_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__srv__EnrollOwner_Request__Sequence__copy(
  const robot_msgs__srv__EnrollOwner_Request__Sequence * input,
  robot_msgs__srv__EnrollOwner_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__srv__EnrollOwner_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_msgs__srv__EnrollOwner_Request * data =
      (robot_msgs__srv__EnrollOwner_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__srv__EnrollOwner_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_msgs__srv__EnrollOwner_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_msgs__srv__EnrollOwner_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `owner_id`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_msgs__srv__EnrollOwner_Response__init(robot_msgs__srv__EnrollOwner_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // owner_id
  if (!rosidl_runtime_c__String__init(&msg->owner_id)) {
    robot_msgs__srv__EnrollOwner_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    robot_msgs__srv__EnrollOwner_Response__fini(msg);
    return false;
  }
  return true;
}

void
robot_msgs__srv__EnrollOwner_Response__fini(robot_msgs__srv__EnrollOwner_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // owner_id
  rosidl_runtime_c__String__fini(&msg->owner_id);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
robot_msgs__srv__EnrollOwner_Response__are_equal(const robot_msgs__srv__EnrollOwner_Response * lhs, const robot_msgs__srv__EnrollOwner_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // owner_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->owner_id), &(rhs->owner_id)))
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
robot_msgs__srv__EnrollOwner_Response__copy(
  const robot_msgs__srv__EnrollOwner_Response * input,
  robot_msgs__srv__EnrollOwner_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // owner_id
  if (!rosidl_runtime_c__String__copy(
      &(input->owner_id), &(output->owner_id)))
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

robot_msgs__srv__EnrollOwner_Response *
robot_msgs__srv__EnrollOwner_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Response * msg = (robot_msgs__srv__EnrollOwner_Response *)allocator.allocate(sizeof(robot_msgs__srv__EnrollOwner_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_msgs__srv__EnrollOwner_Response));
  bool success = robot_msgs__srv__EnrollOwner_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_msgs__srv__EnrollOwner_Response__destroy(robot_msgs__srv__EnrollOwner_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_msgs__srv__EnrollOwner_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_msgs__srv__EnrollOwner_Response__Sequence__init(robot_msgs__srv__EnrollOwner_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Response * data = NULL;

  if (size) {
    data = (robot_msgs__srv__EnrollOwner_Response *)allocator.zero_allocate(size, sizeof(robot_msgs__srv__EnrollOwner_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_msgs__srv__EnrollOwner_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_msgs__srv__EnrollOwner_Response__fini(&data[i - 1]);
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
robot_msgs__srv__EnrollOwner_Response__Sequence__fini(robot_msgs__srv__EnrollOwner_Response__Sequence * array)
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
      robot_msgs__srv__EnrollOwner_Response__fini(&array->data[i]);
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

robot_msgs__srv__EnrollOwner_Response__Sequence *
robot_msgs__srv__EnrollOwner_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_msgs__srv__EnrollOwner_Response__Sequence * array = (robot_msgs__srv__EnrollOwner_Response__Sequence *)allocator.allocate(sizeof(robot_msgs__srv__EnrollOwner_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_msgs__srv__EnrollOwner_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_msgs__srv__EnrollOwner_Response__Sequence__destroy(robot_msgs__srv__EnrollOwner_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_msgs__srv__EnrollOwner_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_msgs__srv__EnrollOwner_Response__Sequence__are_equal(const robot_msgs__srv__EnrollOwner_Response__Sequence * lhs, const robot_msgs__srv__EnrollOwner_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_msgs__srv__EnrollOwner_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_msgs__srv__EnrollOwner_Response__Sequence__copy(
  const robot_msgs__srv__EnrollOwner_Response__Sequence * input,
  robot_msgs__srv__EnrollOwner_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_msgs__srv__EnrollOwner_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_msgs__srv__EnrollOwner_Response * data =
      (robot_msgs__srv__EnrollOwner_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_msgs__srv__EnrollOwner_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_msgs__srv__EnrollOwner_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_msgs__srv__EnrollOwner_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
