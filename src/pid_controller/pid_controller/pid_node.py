#!/usr/bin/env python3

import rclpy
import rclpy.callback_groups
from rclpy.node import Node

from std_msgs.msg import Int16, Int16MultiArray

import numpy as np
from numpy import cos, sin

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller')

        # PWM constants
        self.PWM_MIN: int = -255
        self.PWM_MAX: int = 255

        self.L1: float = 7.5
        self.L2: float = 9.5
        self.M1: float = 0.097
        self.M2: float = 0.097
        self.G: float = 9.81

        # Parámetros independientes para cada motor
        self.motor_params = {
            # Base
            'motor1': {
                'Kp': 1.0,  # Ganancia proporcional
                'Ki': 0.5,  # Ganancia integral
                'Kd': 0.1,      # Ganancia derivativa
                'setpoint': 0.0,  # Setpoint en grados
                'measured_angle': 0.0,  # Valor medido en grados
                'previous_error': 0.0,  # Error anterior
                'integral': 0.0,  # Término integral acumulado
            },
            # End effector
            'motor2': {
                'Kp': 0.030,  # Ganancia proporcional
                'Ki': 0.015,  # Ganancia integral
                'Kd': 0.115,  # Ganancia derivativa
                'setpoint': 30,  # Setpoint en grados
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
        self.inverse_kinematics_sub = self.create_subscription(Int16MultiArray, '/inverse_kinematics', self.inverse_kinematics_callback, 5)

        # Publicador para la señal de control
        self.control1_pub = self.create_publisher(Int16, 'lower_motor', 10)
        self.control2_pub = self.create_publisher(Int16, 'upper_motor', 10)

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop, callback_group=rclpy.callback_groups.MutuallyExclusiveCallbackGroup())

        # Crear el mensaje de control una sola vez
        self.motor1_control_msg: Int16 = Int16()
        self.motor2_control_msg: Int16 = Int16()


    def inverse_kinematics_callback(self, msg: Int16MultiArray) -> None:
        self.motor_params['motor1']['setpoint'] = msg.data[0]
        self.motor_params['motor2']['setpoint'] = msg.data[1]


    def encoder1_callback(self, msg: Int16) -> None:
        self.motor_params['motor1']['measured_angle'] = msg.data


    def encoder2_callback(self, msg: Int16) -> None:
        self.motor_params['motor2']['measured_angle'] = msg.data / 2


    def calculate_M(self, e2, thetaR2, L1, L2, m1, m2):
        sigma1 = L1**2 * m1 + L1**2 * m2 + L2**2 * m2 + 2 * L1 * L2 * m2 * np.cos(e2 + thetaR2)
        M = np.array([
            [sigma1, m2 * L2**2 + L1 * m2 * np.cos(e2 + thetaR2) * L2],
            [m2 * L2**2 + L1 * m2 * np.cos(e2 + thetaR2) * L2, sigma1]
        ])
        return M


    def calculate_C(self, e2, ed1, ed2, thetaR2, L1, L2, m2):
        C = np.array([
            -L1 * L2 * m2 * np.sin(e2 + thetaR2) * (ed2**2 + ed2 + 2 * ed1),
            L1 * L2 * ed1**2 * m2 * np.sin(e2 + thetaR2)
        ])
        return C


    def calculate_G(self, e1, e2, thetaR1, thetaR2, L1, L2, m1, m2, g):
        G_vec = np.array([
            L1 * g * np.cos(e1 + thetaR1) * (m1 + m2) + L2 * g * m2 * np.cos(e1 + e2 + thetaR1 + thetaR2),
            L2 * g * m2 * np.cos(e1 + e2 + thetaR1 + thetaR2)
        ])
        return G_vec


    def calculate_pid(self, params: dict[str, float], error: float) -> float:
        proportional = params['Kp'] * error

        params['integral'] += error * self.dt
        integral = params['Ki'] * params['integral']
        integral = max(min(integral, 100), -100)

        derivative = params['Kd'] * ((error - params['previous_error']) / self.dt)

        # Señal de control final
        return proportional + integral + derivative


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

        # # Obtener los ángulos y velocidades actuales
        # e1 = self.motor_params['motor1']['measured_angle']
        # e2 = self.motor_params['motor2']['measured_angle']
        # ed1 = (e1 - self.motor_params['motor1']['previous_angle']) / self.dt
        # ed2 = (e2 - self.motor_params['motor2']['previous_angle']) / self.dt

        # kp1: float = self.motor_params['motor1']['Kp']
        # kd1: float = self.motor_params['motor1']['Kd']

        # kp2: float = self.motor_params['motor2']['Kp']
        # kd2: float = self.motor_params['motor2']['Kd']

        # # Calcular las matrices y vectores
        # M = self.calculate_M(e1, e2, ed1, ed2, 0, 0, self.L1, self.L2, self.M1, self.M2)
        # C = self.calculate_C(e1, e2, ed1, ed2, 0, 0, self.L1, self.L2, self.M1, self.M2)
        # G = self.calculate_G(e1, e2, 0, 0, self.L1, self.L2, self.M1, self.M2, self.G)

        # # Tau: float = np.array([
        # #     kp1 * e1 + kd1 * ed1 +
        # # ])

        # # Calcular las señales de control
        # control_signals = np.linalg.inv(M) @ (-C - G)

        # # Publicar señales de control
        # self.motor1_control_msg.data = int(control_signals[0])
        # self.motor2_control_msg.data = int(control_signals[1])
        # self.control1_pub.publish(self.motor1_control_msg)
        # self.control2_pub.publish(self.motor2_control_msg)

        # # Actualizar ángulos anteriores
        # self.motor_params['motor1']['previous_angle'] = e1
        # self.motor_params['motor2']['previous_angle'] = e2


def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
