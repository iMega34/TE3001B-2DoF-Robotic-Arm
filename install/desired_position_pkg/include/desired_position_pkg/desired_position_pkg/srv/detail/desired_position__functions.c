// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from desired_position_pkg:srv/DesiredPosition.idl
// generated code does not contain a copyright notice
#include "desired_position_pkg/srv/detail/desired_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
desired_position_pkg__srv__DesiredPosition_Request__init(desired_position_pkg__srv__DesiredPosition_Request * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  return true;
}

void
desired_position_pkg__srv__DesiredPosition_Request__fini(desired_position_pkg__srv__DesiredPosition_Request * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
}

bool
desired_position_pkg__srv__DesiredPosition_Request__are_equal(const desired_position_pkg__srv__DesiredPosition_Request * lhs, const desired_position_pkg__srv__DesiredPosition_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  return true;
}

bool
desired_position_pkg__srv__DesiredPosition_Request__copy(
  const desired_position_pkg__srv__DesiredPosition_Request * input,
  desired_position_pkg__srv__DesiredPosition_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

desired_position_pkg__srv__DesiredPosition_Request *
desired_position_pkg__srv__DesiredPosition_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Request * msg = (desired_position_pkg__srv__DesiredPosition_Request *)allocator.allocate(sizeof(desired_position_pkg__srv__DesiredPosition_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(desired_position_pkg__srv__DesiredPosition_Request));
  bool success = desired_position_pkg__srv__DesiredPosition_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
desired_position_pkg__srv__DesiredPosition_Request__destroy(desired_position_pkg__srv__DesiredPosition_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    desired_position_pkg__srv__DesiredPosition_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__init(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Request * data = NULL;

  if (size) {
    data = (desired_position_pkg__srv__DesiredPosition_Request *)allocator.zero_allocate(size, sizeof(desired_position_pkg__srv__DesiredPosition_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = desired_position_pkg__srv__DesiredPosition_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        desired_position_pkg__srv__DesiredPosition_Request__fini(&data[i - 1]);
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
desired_position_pkg__srv__DesiredPosition_Request__Sequence__fini(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array)
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
      desired_position_pkg__srv__DesiredPosition_Request__fini(&array->data[i]);
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

desired_position_pkg__srv__DesiredPosition_Request__Sequence *
desired_position_pkg__srv__DesiredPosition_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Request__Sequence * array = (desired_position_pkg__srv__DesiredPosition_Request__Sequence *)allocator.allocate(sizeof(desired_position_pkg__srv__DesiredPosition_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = desired_position_pkg__srv__DesiredPosition_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
desired_position_pkg__srv__DesiredPosition_Request__Sequence__destroy(desired_position_pkg__srv__DesiredPosition_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    desired_position_pkg__srv__DesiredPosition_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__are_equal(const desired_position_pkg__srv__DesiredPosition_Request__Sequence * lhs, const desired_position_pkg__srv__DesiredPosition_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!desired_position_pkg__srv__DesiredPosition_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
desired_position_pkg__srv__DesiredPosition_Request__Sequence__copy(
  const desired_position_pkg__srv__DesiredPosition_Request__Sequence * input,
  desired_position_pkg__srv__DesiredPosition_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(desired_position_pkg__srv__DesiredPosition_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    desired_position_pkg__srv__DesiredPosition_Request * data =
      (desired_position_pkg__srv__DesiredPosition_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!desired_position_pkg__srv__DesiredPosition_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          desired_position_pkg__srv__DesiredPosition_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!desired_position_pkg__srv__DesiredPosition_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
desired_position_pkg__srv__DesiredPosition_Response__init(desired_position_pkg__srv__DesiredPosition_Response * msg)
{
  if (!msg) {
    return false;
  }
  // theta1
  // theta2
  return true;
}

void
desired_position_pkg__srv__DesiredPosition_Response__fini(desired_position_pkg__srv__DesiredPosition_Response * msg)
{
  if (!msg) {
    return;
  }
  // theta1
  // theta2
}

bool
desired_position_pkg__srv__DesiredPosition_Response__are_equal(const desired_position_pkg__srv__DesiredPosition_Response * lhs, const desired_position_pkg__srv__DesiredPosition_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // theta1
  if (lhs->theta1 != rhs->theta1) {
    return false;
  }
  // theta2
  if (lhs->theta2 != rhs->theta2) {
    return false;
  }
  return true;
}

bool
desired_position_pkg__srv__DesiredPosition_Response__copy(
  const desired_position_pkg__srv__DesiredPosition_Response * input,
  desired_position_pkg__srv__DesiredPosition_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // theta1
  output->theta1 = input->theta1;
  // theta2
  output->theta2 = input->theta2;
  return true;
}

desired_position_pkg__srv__DesiredPosition_Response *
desired_position_pkg__srv__DesiredPosition_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Response * msg = (desired_position_pkg__srv__DesiredPosition_Response *)allocator.allocate(sizeof(desired_position_pkg__srv__DesiredPosition_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(desired_position_pkg__srv__DesiredPosition_Response));
  bool success = desired_position_pkg__srv__DesiredPosition_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
desired_position_pkg__srv__DesiredPosition_Response__destroy(desired_position_pkg__srv__DesiredPosition_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    desired_position_pkg__srv__DesiredPosition_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__init(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Response * data = NULL;

  if (size) {
    data = (desired_position_pkg__srv__DesiredPosition_Response *)allocator.zero_allocate(size, sizeof(desired_position_pkg__srv__DesiredPosition_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = desired_position_pkg__srv__DesiredPosition_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        desired_position_pkg__srv__DesiredPosition_Response__fini(&data[i - 1]);
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
desired_position_pkg__srv__DesiredPosition_Response__Sequence__fini(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array)
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
      desired_position_pkg__srv__DesiredPosition_Response__fini(&array->data[i]);
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

desired_position_pkg__srv__DesiredPosition_Response__Sequence *
desired_position_pkg__srv__DesiredPosition_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  desired_position_pkg__srv__DesiredPosition_Response__Sequence * array = (desired_position_pkg__srv__DesiredPosition_Response__Sequence *)allocator.allocate(sizeof(desired_position_pkg__srv__DesiredPosition_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = desired_position_pkg__srv__DesiredPosition_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
desired_position_pkg__srv__DesiredPosition_Response__Sequence__destroy(desired_position_pkg__srv__DesiredPosition_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    desired_position_pkg__srv__DesiredPosition_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__are_equal(const desired_position_pkg__srv__DesiredPosition_Response__Sequence * lhs, const desired_position_pkg__srv__DesiredPosition_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!desired_position_pkg__srv__DesiredPosition_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
desired_position_pkg__srv__DesiredPosition_Response__Sequence__copy(
  const desired_position_pkg__srv__DesiredPosition_Response__Sequence * input,
  desired_position_pkg__srv__DesiredPosition_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(desired_position_pkg__srv__DesiredPosition_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    desired_position_pkg__srv__DesiredPosition_Response * data =
      (desired_position_pkg__srv__DesiredPosition_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!desired_position_pkg__srv__DesiredPosition_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          desired_position_pkg__srv__DesiredPosition_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!desired_position_pkg__srv__DesiredPosition_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
