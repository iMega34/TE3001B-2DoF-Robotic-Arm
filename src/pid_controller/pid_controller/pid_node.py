#!/usr/bin/env python3

import rclpy
import rclpy.callback_groups
from rclpy.node import Node

from std_msgs.msg import Int16

from math import sin

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller')

        # PWM constants
        self.PWM_MIN: int = -255
        self.PWM_MAX: int = 255

        # Link's constants
        self.M: int = 0.097
        self.G: float = 9.81
        self.L: float = 7.5
        self.SCALE: int = 10

        # Parámetros independientes para cada motor
        self.motor_params = {
            # Base
            'motor1': {
                'Kp': 0.70,  # Ganancia proporcional
                'Ki': 0.70,  # Ganancia integral
                'Kd': 0.001,      # Ganancia derivativa
                'setpoint': 45,  # Setpoint en grados
                'measured_angle': 0.0,  # Valor medido en grados
                'previous_error': 0.0,  # Error anterior
                'integral': 0.0,  # Término integral acumulado
            },
            # End effector
            'motor2': {
                'Kp': 0.35,  # Ganancia proporcional
                'Ki': 0.0035,  # Ganancia integral
                'Kd': 0.0,  # Ganancia derivativa
                'setpoint': 0.0,  # Setpoint en grados
                'measured_angle': 0.0,  # Valor medido en grados
                'previous_error': 0.0,  # Error anterior
                'integral': 0.0,  # Término integral acumulado
            }
        }

        # Intervalo de tiempo (en segundos)
        self.dt: float = 0.05

        # Margen de error para detener el controlador (en grados)
        self.error_margin: int = 10

        # Subscriptor para el valor medido (posición en grados)
        self.encoder1_sub = self.create_subscription(Int16, '/lower_encoder', self.encoder1_callback, 5)
        self.encoder2_sub = self.create_subscription(Int16, '/upper_encoder', self.encoder2_callback, 5)

        # Publicador para la señal de control
        self.control1_pub = self.create_publisher(Int16, 'lower_motor', 10)
        self.control2_pub = self.create_publisher(Int16, 'upper_motor', 10)

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop, callback_group=rclpy.callback_groups.MutuallyExclusiveCallbackGroup())

        # Crear el mensaje de control una sola vez
        self.motor1_control_msg: Int16 = Int16()
        self.motor2_control_msg: Int16 = Int16()


    def encoder1_callback(self, msg: Int16):
        self.motor_params['motor1']['measured_angle'] = msg.data


    def encoder2_callback(self, msg: Int16):
        self.motor_params['motor2']['measured_angle'] = msg.data


    def calculate_pid(self, params: dict[str, float], error: float) -> float:
        angle: int = params['measured_angle']
        proportional = params['Kp'] * error

        params['integral'] += error * self.dt
        integral = params['Ki'] * params['integral']
        integral = max(min(integral, 100), -100)

        derivative = params['Kd'] * ((error - params['previous_error']) / self.dt)

        # gravity_compensation: float = self.calculate_gravity_compensation(angle)

        # Señal de control final
        return proportional + integral + derivative


    def calculate_gravity_compensation(self, angle: int) -> float:
        angle_rad: float = angle * (3.1416 / 180.0)
        tau_g = self.M * self.G * self.L * sin(angle_rad)
        gravity_compensation: float = tau_g * self.SCALE

        return gravity_compensation


    def clamp(self, control_signal: float) -> int:
        return max(min(control_signal, self.PWM_MAX), self.PWM_MIN)


    def control_loop(self):
        # Lista para almacenar las señales de control
        control_signals = []

        for motor in ['motor1', 'motor2']:
            params = self.motor_params[motor]

            # Calcular el error (en grados)
            error = params['setpoint'] - params['measured_angle']

            self.get_logger().info(f"{motor}: Error = {error} grados, Ángulo medido = {params['measured_angle']} grados, Setpoint = {params['setpoint']} grados")

            # Control PID
            control_signal: float = self.calculate_pid(params, error)
            control_signal: int = self.clamp(control_signal)

            # Guardar señal de control
            control_signals.append(int(control_signal))

            # Actualizar error anterior
            params['previous_error'] = error

        # Publicar señales de control
        self.motor1_control_msg.data = control_signals[0]
        self.motor2_control_msg.data = control_signals[1]
        self.control1_pub.publish(self.motor1_control_msg)
        self.control2_pub.publish(self.motor2_control_msg)


def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()