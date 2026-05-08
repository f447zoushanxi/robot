// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_msgs:srv/FindPerson.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__STRUCT_HPP_
#define ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_msgs__srv__FindPerson_Request __attribute__((deprecated))
#else
# define DEPRECATED__robot_msgs__srv__FindPerson_Request __declspec(deprecated)
#endif

namespace robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct FindPerson_Request_
{
  using Type = FindPerson_Request_<ContainerAllocator>;

  explicit FindPerson_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hint_name = "";
      this->timeout_sec = 0.0f;
    }
  }

  explicit FindPerson_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : hint_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hint_name = "";
      this->timeout_sec = 0.0f;
    }
  }

  // field types and members
  using _hint_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _hint_name_type hint_name;
  using _timeout_sec_type =
    float;
  _timeout_sec_type timeout_sec;

  // setters for named parameter idiom
  Type & set__hint_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->hint_name = _arg;
    return *this;
  }
  Type & set__timeout_sec(
    const float & _arg)
  {
    this->timeout_sec = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_msgs::srv::FindPerson_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_msgs::srv::FindPerson_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::FindPerson_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::FindPerson_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_msgs__srv__FindPerson_Request
    std::shared_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_msgs__srv__FindPerson_Request
    std::shared_ptr<robot_msgs::srv::FindPerson_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FindPerson_Request_ & other) const
  {
    if (this->hint_name != other.hint_name) {
      return false;
    }
    if (this->timeout_sec != other.timeout_sec) {
      return false;
    }
    return true;
  }
  bool operator!=(const FindPerson_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FindPerson_Request_

// alias to use template instance with default allocator
using FindPerson_Request =
  robot_msgs::srv::FindPerson_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_msgs


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_msgs__srv__FindPerson_Response __attribute__((deprecated))
#else
# define DEPRECATED__robot_msgs__srv__FindPerson_Response __declspec(deprecated)
#endif

namespace robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct FindPerson_Response_
{
  using Type = FindPerson_Response_<ContainerAllocator>;

  explicit FindPerson_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->found = false;
      this->confidence = 0.0f;
      this->identity = "";
      this->message = "";
    }
  }

  explicit FindPerson_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc, _init),
    identity(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->found = false;
      this->confidence = 0.0f;
      this->identity = "";
      this->message = "";
    }
  }

  // field types and members
  using _found_type =
    bool;
  _found_type found;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _identity_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _identity_type identity;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__found(
    const bool & _arg)
  {
    this->found = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__identity(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->identity = _arg;
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
    robot_msgs::srv::FindPerson_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_msgs::srv::FindPerson_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::FindPerson_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_msgs::srv::FindPerson_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_msgs__srv__FindPerson_Response
    std::shared_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_msgs__srv__FindPerson_Response
    std::shared_ptr<robot_msgs::srv::FindPerson_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FindPerson_Response_ & other) const
  {
    if (this->found != other.found) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->identity != other.identity) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const FindPerson_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FindPerson_Response_

// alias to use template instance with default allocator
using FindPerson_Response =
  robot_msgs::srv::FindPerson_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_msgs

namespace robot_msgs
{

namespace srv
{

struct FindPerson
{
  using Request = robot_msgs::srv::FindPerson_Request;
  using Response = robot_msgs::srv::FindPerson_Response;
};

}  // namespace srv

}  // namespace robot_msgs

#endif  // ROBOT_MSGS__SRV__DETAIL__FIND_PERSON__STRUCT_HPP_
