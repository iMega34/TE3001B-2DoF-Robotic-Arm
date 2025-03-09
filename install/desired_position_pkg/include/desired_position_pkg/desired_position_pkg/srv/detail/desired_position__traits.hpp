// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice

#ifndef DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__TRAITS_HPP_
#define DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "desired_position_pkg/srv/detail/desired_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace desired_position_pkg
{

namespace srv
{

inline void to_flow_style_yaml(
  const DesiredPosition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DesiredPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DesiredPosition_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace desired_position_pkg

namespace rosidl_generator_traits
{

[[deprecated("use desired_position_pkg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const desired_position_pkg::srv::DesiredPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  desired_position_pkg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use desired_position_pkg::srv::to_yaml() instead")]]
inline std::string to_yaml(const desired_position_pkg::srv::DesiredPosition_Request & msg)
{
  return desired_position_pkg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<desired_position_pkg::srv::DesiredPosition_Request>()
{
  return "desired_position_pkg::srv::DesiredPosition_Request";
}

template<>
inline const char * name<desired_position_pkg::srv::DesiredPosition_Request>()
{
  return "desired_position_pkg/srv/DesiredPosition_Request";
}

template<>
struct has_fixed_size<desired_position_pkg::srv::DesiredPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<desired_position_pkg::srv::DesiredPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<desired_position_pkg::srv::DesiredPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace desired_position_pkg
{

namespace srv
{

inline void to_flow_style_yaml(
  const DesiredPosition_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: theta1
  {
    out << "theta1: ";
    rosidl_generator_traits::value_to_yaml(msg.theta1, out);
    out << ", ";
  }

  // member: theta2
  {
    out << "theta2: ";
    rosidl_generator_traits::value_to_yaml(msg.theta2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DesiredPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: theta1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "theta1: ";
    rosidl_generator_traits::value_to_yaml(msg.theta1, out);
    out << "\n";
  }

  // member: theta2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "theta2: ";
    rosidl_generator_traits::value_to_yaml(msg.theta2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DesiredPosition_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace desired_position_pkg

namespace rosidl_generator_traits
{

[[deprecated("use desired_position_pkg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const desired_position_pkg::srv::DesiredPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  desired_position_pkg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use desired_position_pkg::srv::to_yaml() instead")]]
inline std::string to_yaml(const desired_position_pkg::srv::DesiredPosition_Response & msg)
{
  return desired_position_pkg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<desired_position_pkg::srv::DesiredPosition_Response>()
{
  return "desired_position_pkg::srv::DesiredPosition_Response";
}

template<>
inline const char * name<desired_position_pkg::srv::DesiredPosition_Response>()
{
  return "desired_position_pkg/srv/DesiredPosition_Response";
}

template<>
struct has_fixed_size<desired_position_pkg::srv::DesiredPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<desired_position_pkg::srv::DesiredPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<desired_position_pkg::srv::DesiredPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<desired_position_pkg::srv::DesiredPosition>()
{
  return "desired_position_pkg::srv::DesiredPosition";
}

template<>
inline const char * name<desired_position_pkg::srv::DesiredPosition>()
{
  return "desired_position_pkg/srv/DesiredPosition";
}

template<>
struct has_fixed_size<desired_position_pkg::srv::DesiredPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<desired_position_pkg::srv::DesiredPosition_Request>::value &&
    has_fixed_size<desired_position_pkg::srv::DesiredPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<desired_position_pkg::srv::DesiredPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<desired_position_pkg::srv::DesiredPosition_Request>::value &&
    has_bounded_size<desired_position_pkg::srv::DesiredPosition_Response>::value
  >
{
};

template<>
struct is_service<desired_position_pkg::srv::DesiredPosition>
  : std::true_type
{
};

template<>
struct is_service_request<desired_position_pkg::srv::DesiredPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<desired_position_pkg::srv::DesiredPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__TRAITS_HPP_
