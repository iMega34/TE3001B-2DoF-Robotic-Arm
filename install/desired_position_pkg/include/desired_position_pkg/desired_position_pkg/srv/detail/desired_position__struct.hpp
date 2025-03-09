// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice

#ifndef DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_HPP_
#define DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__desired_position_pkg__srv__DesiredPosition_Request __attribute__((deprecated))
#else
# define DEPRECATED__desired_position_pkg__srv__DesiredPosition_Request __declspec(deprecated)
#endif

namespace desired_position_pkg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DesiredPosition_Request_
{
  using Type = DesiredPosition_Request_<ContainerAllocator>;

  explicit DesiredPosition_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0;
      this->y = 0;
    }
  }

  explicit DesiredPosition_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0;
      this->y = 0;
    }
  }

  // field types and members
  using _x_type =
    int16_t;
  _x_type x;
  using _y_type =
    int16_t;
  _y_type y;

  // setters for named parameter idiom
  Type & set__x(
    const int16_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int16_t & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__desired_position_pkg__srv__DesiredPosition_Request
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__desired_position_pkg__srv__DesiredPosition_Request
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DesiredPosition_Request_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const DesiredPosition_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DesiredPosition_Request_

// alias to use template instance with default allocator
using DesiredPosition_Request =
  desired_position_pkg::srv::DesiredPosition_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace desired_position_pkg


#ifndef _WIN32
# define DEPRECATED__desired_position_pkg__srv__DesiredPosition_Response __attribute__((deprecated))
#else
# define DEPRECATED__desired_position_pkg__srv__DesiredPosition_Response __declspec(deprecated)
#endif

namespace desired_position_pkg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DesiredPosition_Response_
{
  using Type = DesiredPosition_Response_<ContainerAllocator>;

  explicit DesiredPosition_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->theta1 = 0;
      this->theta2 = 0;
    }
  }

  explicit DesiredPosition_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->theta1 = 0;
      this->theta2 = 0;
    }
  }

  // field types and members
  using _theta1_type =
    int16_t;
  _theta1_type theta1;
  using _theta2_type =
    int16_t;
  _theta2_type theta2;

  // setters for named parameter idiom
  Type & set__theta1(
    const int16_t & _arg)
  {
    this->theta1 = _arg;
    return *this;
  }
  Type & set__theta2(
    const int16_t & _arg)
  {
    this->theta2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__desired_position_pkg__srv__DesiredPosition_Response
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__desired_position_pkg__srv__DesiredPosition_Response
    std::shared_ptr<desired_position_pkg::srv::DesiredPosition_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DesiredPosition_Response_ & other) const
  {
    if (this->theta1 != other.theta1) {
      return false;
    }
    if (this->theta2 != other.theta2) {
      return false;
    }
    return true;
  }
  bool operator!=(const DesiredPosition_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DesiredPosition_Response_

// alias to use template instance with default allocator
using DesiredPosition_Response =
  desired_position_pkg::srv::DesiredPosition_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace desired_position_pkg

namespace desired_position_pkg
{

namespace srv
{

struct DesiredPosition
{
  using Request = desired_position_pkg::srv::DesiredPosition_Request;
  using Response = desired_position_pkg::srv::DesiredPosition_Response;
};

}  // namespace srv

}  // namespace desired_position_pkg

#endif  // DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_HPP_
