// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_msgs:srv/EnrollOwner.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_HPP_
#define ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_msgs__srv__EnrollOwner_Request __attribute__((deprecated))
#else
# define DEPRECATED__robot_msgs__srv__EnrollOwner_Request __declspec(deprecated)
#endif

namespace robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EnrollOwner_Request_
{
  using Type = EnrollOwner_Request_<ContainerAllocator>;

  explicit EnrollOwner_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->require_physical_confirm = false;
      this->window_sec = 0.0f;
    }
  }

  explicit EnrollOwner_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->require_physical_confirm = false;
      this->window_sec = 0.0f;
    }
  }

  // field types and members
  using _require_physical_confirm_type =
    bool;
  _require_physical_confirm_type require_physical_confirm;
  using _window_sec_type =
    float;
  _window_sec_type window_sec;

  // setters for named parameter idiom
  Type & set__require_physical_confirm(
    const bool & _arg)
  {
    this->require_physical_confirm = _arg;
    return *this;
  }
  Type & set__window_sec(
    const float & _arg)
  {
    this->window_sec = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_msgs__srv__EnrollOwner_Request
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_msgs__srv__EnrollOwner_Request
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EnrollOwner_Request_ & other) const
  {
    if (this->require_physical_confirm != other.require_physical_confirm) {
      return false;
    }
    if (this->window_sec != other.window_sec) {
      return false;
    }
    return true;
  }
  bool operator!=(const EnrollOwner_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EnrollOwner_Request_

// alias to use template instance with default allocator
using EnrollOwner_Request =
  robot_msgs::srv::EnrollOwner_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_msgs


#ifndef _WIN32
# define DEPRECATED__robot_msgs__srv__EnrollOwner_Response __attribute__((deprecated))
#else
# define DEPRECATED__robot_msgs__srv__EnrollOwner_Response __declspec(deprecated)
#endif

namespace robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EnrollOwner_Response_
{
  using Type = EnrollOwner_Response_<ContainerAllocator>;

  explicit EnrollOwner_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
      this->owner_id = "";
      this->message = "";
    }
  }

  explicit EnrollOwner_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : owner_id(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
      this->owner_id = "";
      this->message = "";
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _owner_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _owner_id_type owner_id;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__owner_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->owner_id = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_msgs__srv__EnrollOwner_Response
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_msgs__srv__EnrollOwner_Response
    std::shared_ptr<robot_msgs::srv::EnrollOwner_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EnrollOwner_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->owner_id != other.owner_id) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const EnrollOwner_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EnrollOwner_Response_

// alias to use template instance with default allocator
using EnrollOwner_Response =
  robot_msgs::srv::EnrollOwner_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_msgs

namespace robot_msgs
{

namespace srv
{

struct EnrollOwner
{
  using Request = robot_msgs::srv::EnrollOwner_Request;
  using Response = robot_msgs::srv::EnrollOwner_Response;
};

}  // namespace srv

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__SRV__DETAIL__ENROLL_OWNER__STRUCT_HPP_
