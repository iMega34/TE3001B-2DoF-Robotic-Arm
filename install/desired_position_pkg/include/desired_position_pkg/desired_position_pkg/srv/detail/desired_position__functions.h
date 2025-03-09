// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice

#ifndef DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__FUNCTIONS_H_
#define DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "desired_position_pkg/msg/rosidl_generator_c__visibility_control.h"

#include "desired_position_pkg/srv/detail/desired_position__struct.h"

/// Initialize srv/DesiredPosition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * desired_position_pkg__srv__DesiredPosition_Request
 * )) before or use
 * desired_position_pkg__srv__DesiredPosition_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__init(desired_position_pkg__srv__DesiredPosition_Request * msg);

/// Finalize srv/DesiredPosition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Request__fini(desired_position_pkg__srv__DesiredPosition_Request * msg);

/// Create srv/DesiredPosition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * desired_position_pkg__srv__DesiredPosition_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
desired_position_pkg__srv__DesiredPosition_Request *
desired_position_pkg__srv__DesiredPosition_Request__create();

/// Destroy srv/DesiredPosition message.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Request__destroy(desired_position_pkg__srv__DesiredPosition_Request * msg);

/// Check for srv/DesiredPosition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__are_equal(const desired_position_pkg__srv__DesiredPosition_Request * lhs, const desired_position_pkg__srv__DesiredPosition_Request * rhs);

/// Copy a srv/DesiredPosition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__copy(
  const desired_position_pkg__srv__DesiredPosition_Request * input,
  desired_position_pkg__srv__DesiredPosition_Request * output);

/// Initialize array of srv/DesiredPosition messages.
/**
 * It allocates the memory for the number of elements and calls
 * desired_position_pkg__srv__DesiredPosition_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__init(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array, size_t size);

/// Finalize array of srv/DesiredPosition messages.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Request__Sequence__fini(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array);

/// Create array of srv/DesiredPosition messages.
/**
 * It allocates the memory for the array and calls
 * desired_position_pkg__srv__DesiredPosition_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
desired_position_pkg__srv__DesiredPosition_Request__Sequence *
desired_position_pkg__srv__DesiredPosition_Request__Sequence__create(size_t size);

/// Destroy array of srv/DesiredPosition messages.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Request__Sequence__destroy(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array);

/// Check for srv/DesiredPosition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__are_equal(const desired_position_pkg__srv__DesiredPosition_Request__Sequence * lhs, const desired_position_pkg__srv__DesiredPosition_Request__Sequence * rhs);

/// Copy an array of srv/DesiredPosition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__copy(
  const desired_position_pkg__srv__DesiredPosition_Request__Sequence * input,
  desired_position_pkg__srv__DesiredPosition_Request__Sequence * output);

/// Initialize srv/DesiredPosition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * desired_position_pkg__srv__DesiredPosition_Response
 * )) before or use
 * desired_position_pkg__srv__DesiredPosition_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__init(desired_position_pkg__srv__DesiredPosition_Response * msg);

/// Finalize srv/DesiredPosition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Response__fini(desired_position_pkg__srv__DesiredPosition_Response * msg);

/// Create srv/DesiredPosition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * desired_position_pkg__srv__DesiredPosition_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
desired_position_pkg__srv__DesiredPosition_Response *
desired_position_pkg__srv__DesiredPosition_Response__create();

/// Destroy srv/DesiredPosition message.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Response__destroy(desired_position_pkg__srv__DesiredPosition_Response * msg);

/// Check for srv/DesiredPosition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__are_equal(const desired_position_pkg__srv__DesiredPosition_Response * lhs, const desired_position_pkg__srv__DesiredPosition_Response * rhs);

/// Copy a srv/DesiredPosition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__copy(
  const desired_position_pkg__srv__DesiredPosition_Response * input,
  desired_position_pkg__srv__DesiredPosition_Response * output);

/// Initialize array of srv/DesiredPosition messages.
/**
 * It allocates the memory for the number of elements and calls
 * desired_position_pkg__srv__DesiredPosition_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__init(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array, size_t size);

/// Finalize array of srv/DesiredPosition messages.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Response__Sequence__fini(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array);

/// Create array of srv/DesiredPosition messages.
/**
 * It allocates the memory for the array and calls
 * desired_position_pkg__srv__DesiredPosition_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
desired_position_pkg__srv__DesiredPosition_Response__Sequence *
desired_position_pkg__srv__DesiredPosition_Response__Sequence__create(size_t size);

/// Destroy array of srv/DesiredPosition messages.
/**
 * It calls
 * desired_position_pkg__srv__DesiredPosition_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
void
desired_position_pkg__srv__DesiredPosition_Response__Sequence__destroy(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array);

/// Check for srv/DesiredPosition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__are_equal(const desired_position_pkg__srv__DesiredPosition_Response__Sequence * lhs, const desired_position_pkg__srv__DesiredPosition_Response__Sequence * rhs);

/// Copy an array of srv/DesiredPosition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_desired_position_pkg
bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__copy(
  const desired_position_pkg__srv__DesiredPosition_Response__Sequence * input,
  desired_position_pkg__srv__DesiredPosition_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DESIRED_POSITION_PKG__SRV__DETAIL__DESIRED_POSITION__FUNCTIONS_H_
