// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice

#ifndef DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_H_
#define DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/DesiredPosition in the package desired_position_pkg.
typedef struct desired_position_pkg__srv__DesiredPosition_Request
{
  int16_t x;
  int16_t y;
} desired_position_pkg__srv__DesiredPosition_Request;

// Struct for a sequence of desired_position_pkg__srv__DesiredPosition_Request.
typedef struct desired_position_pkg__srv__DesiredPosition_Request__Sequence
{
  desired_position_pkg__srv__DesiredPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} desired_position_pkg__srv__DesiredPosition_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/DesiredPosition in the package desired_position_pkg.
typedef struct desired_position_pkg__srv__DesiredPosition_Response
{
  int16_t theta1;
  int16_t theta2;
} desired_position_pkg__srv__DesiredPosition_Response;

// Struct for a sequence of desired_position_pkg__srv__DesiredPosition_Response.
typedef struct desired_position_pkg__srv__DesiredPosition_Response__Sequence
{
  desired_position_pkg__srv__DesiredPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} desired_position_pkg__srv__DesiredPosition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__STRUCT_H_
