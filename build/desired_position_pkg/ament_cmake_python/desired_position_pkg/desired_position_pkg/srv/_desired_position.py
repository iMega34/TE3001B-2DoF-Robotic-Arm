# generated from rosidl_generator_py/resource/_idl.py.em
# with input from desired_position_pkg:srv/DesiredPosition.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DesiredPosition_Request(type):
    """Metaclass of message 'DesiredPosition_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('desired_position_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'desired_position_pkg.srv.DesiredPosition_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__desired_position__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__desired_position__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__desired_position__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__desired_position__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__desired_position__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DesiredPosition_Request(metaclass=Metaclass_DesiredPosition_Request):
    """Message class 'DesiredPosition_Request'."""

    __slots__ = [
        '_x',
        '_y',
    ]

    _fields_and_field_types = {
        'x': 'int16',
        'y': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.x = kwargs.get('x', int())
        self.y = kwargs.get('y', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'x' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'x' field must be an integer in [-32768, 32767]"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'y' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'y' field must be an integer in [-32768, 32767]"
        self._y = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_DesiredPosition_Response(type):
    """Metaclass of message 'DesiredPosition_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('desired_position_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'desired_position_pkg.srv.DesiredPosition_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__desired_position__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__desired_position__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__desired_position__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__desired_position__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__desired_position__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DesiredPosition_Response(metaclass=Metaclass_DesiredPosition_Response):
    """Message class 'DesiredPosition_Response'."""

    __slots__ = [
        '_theta1',
        '_theta2',
    ]

    _fields_and_field_types = {
        'theta1': 'int16',
        'theta2': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.theta1 = kwargs.get('theta1', int())
        self.theta2 = kwargs.get('theta2', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.theta1 != other.theta1:
            return False
        if self.theta2 != other.theta2:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def theta1(self):
        """Message field 'theta1'."""
        return self._theta1

    @theta1.setter
    def theta1(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'theta1' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'theta1' field must be an integer in [-32768, 32767]"
        self._theta1 = value

    @builtins.property
    def theta2(self):
        """Message field 'theta2'."""
        return self._theta2

    @theta2.setter
    def theta2(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'theta2' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'theta2' field must be an integer in [-32768, 32767]"
        self._theta2 = value


class Metaclass_DesiredPosition(type):
    """Metaclass of service 'DesiredPosition'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('desired_position_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'desired_position_pkg.srv.DesiredPosition')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__desired_position

            from desired_position_pkg.srv import _desired_position
            if _desired_position.Metaclass_DesiredPosition_Request._TYPE_SUPPORT is None:
                _desired_position.Metaclass_DesiredPosition_Request.__import_type_support__()
            if _desired_position.Metaclass_DesiredPosition_Response._TYPE_SUPPORT is None:
                _desired_position.Metaclass_DesiredPosition_Response.__import_type_support__()


class DesiredPosition(metaclass=Metaclass_DesiredPosition):
    from desired_position_pkg.srv._desired_position import DesiredPosition_Request as Request
    from desired_position_pkg.srv._desired_position import DesiredPosition_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
