// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice

#ifndef DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__BUILDER_HPP_
#define DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "desired_position_pkg/srv/detail/desired_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace desired_position_pkg
{

namespace srv
{

namespace builder
{

class Init_DesiredPosition_Request_y
{
public:
  explicit Init_DesiredPosition_Request_y(::desired_position_pkg::srv::DesiredPosition_Request & msg)
  : msg_(msg)
  {}
  ::desired_position_pkg::srv::DesiredPosition_Request y(::desired_position_pkg::srv::DesiredPosition_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::desired_position_pkg::srv::DesiredPosition_Request msg_;
};

class Init_DesiredPosition_Request_x
{
public:
  Init_DesiredPosition_Request_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DesiredPosition_Request_y x(::desired_position_pkg::srv::DesiredPosition_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_DesiredPosition_Request_y(msg_);
  }

private:
  ::desired_position_pkg::srv::DesiredPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::desired_position_pkg::srv::DesiredPosition_Request>()
{
  return desired_position_pkg::srv::builder::Init_DesiredPosition_Request_x();
}

}  // namespace desired_position_pkg


namespace desired_position_pkg
{

namespace srv
{

namespace builder
{

class Init_DesiredPosition_Response_theta2
{
public:
  explicit Init_DesiredPosition_Response_theta2(::desired_position_pkg::srv::DesiredPosition_Response & msg)
  : msg_(msg)
  {}
  ::desired_position_pkg::srv::DesiredPosition_Response theta2(::desired_position_pkg::srv::DesiredPosition_Response::_theta2_type arg)
  {
    msg_.theta2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::desired_position_pkg::srv::DesiredPosition_Response msg_;
};

class Init_DesiredPosition_Response_theta1
{
public:
  Init_DesiredPosition_Response_theta1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DesiredPosition_Response_theta2 theta1(::desired_position_pkg::srv::DesiredPosition_Response::_theta1_type arg)
  {
    msg_.theta1 = std::move(arg);
    return Init_DesiredPosition_Response_theta2(msg_);
  }

private:
  ::desired_position_pkg::srv::DesiredPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::desired_position_pkg::srv::DesiredPosition_Response>()
{
  return desired_position_pkg::srv::builder::Init_DesiredPosition_Response_theta1();
}

}  // namespace desired_position_pkg

#endif  // DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__BUILDER_HPP_
