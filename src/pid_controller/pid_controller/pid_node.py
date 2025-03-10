#!/usr/bin/env python3

import rclpy
import rclpy.callback_groups
from rclpy.node import Node

from std_msgs.msg import Int16

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller')

        # Parámetros independientes para cada motor
        self.motor_params = {
            # Base
            'motor1': {
                'Kp': 0.55273,
                'Ki': 0.20,
                'Kd': 0.0,
                'setpoint': -20,
                'measured_angle': 0.0,
                'previous_error': 0.0,
                'integral': 0.0
            },
            # End effector
            'motor2': {
                'Kp': 0.50,
                'Ki': 0.20,
                'Kd': 0.0,
                'setpoint': 90,
                'measured_angle': 0.0,
                'previous_error': 0.0,
                'integral': 0.0
            }
        }

        # Intervalo de tiempo (en segundos)
        self.dt = 0.1

        # Margen de error para detener el controlador (en grados)
        self.error_margin = 15

        # Bandera para habilitar/deshabilitar el control
        self.control_active = True

        # Subscriptor para el valor medido (posición en grados)
        self.encoder1_sub = self.create_subscription(Int16, '/lower_encoder', self.encoder1_callback, 5)
        self.encoder2_sub = self.create_subscription(Int16, '/upper_encoder', self.encoder2_callback, 5)

        # Publicador para la señal de control
        self.control1_pub = self.create_publisher(Int16, 'lower_motor', 10)
        self.control2_pub = self.create_publisher(Int16, 'upper_motor', 10)

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop, callback_group=rclpy.callback_groups.MutuallyExclusiveCallbackGroup())

        # Crear el mensaje de control una sola vez
        self.motor1_control_msg = Int16()
        self.motor2_control_msg = Int16()


    def encoder1_callback(self, msg):
        self.motor_params['motor1']['measured_angle'] = msg.data
        # if self.get_clock().now().nanoseconds % 10 == 0:
            # self.get_logger().info(f"Motor1: Posición medida = {self.motor_params['motor1']['measured_angle']} grados")


    def encoder2_callback(self, msg):
        self.motor_params['motor2']['measured_angle'] = msg.data
        # if self.get_clock().now().nanoseconds % 10 == 0:
            # self.get_logger().info(f"Motor2: Posición medida = {self.motor_params['motor2']['measured_angle']} grados")


    def control_loop(self):
        if not self.control_active:
            return

        # Bandera para verificar si ambos motores han alcanzado el setpoint
        all_motors_reached_setpoint = True  

        # Lista para almacenar las señales de control
        control_signals = []

        for motor in ['motor1', 'motor2']:
            params = self.motor_params[motor]

            # Calcular el error (en grados)
            error = params['setpoint'] - params['measured_angle']

            self.get_logger().info(
                f"{motor}: Error = {error} grados, Ángulo medido = {params['measured_angle']} grados, Setpoint = {params['setpoint']} grados"
            )

            # Verificar si el error está dentro del margen de error
            if abs(error) < self.error_margin:
                self.get_logger().info(f"{motor}: Setpoint alcanzado, deteniendo motor.")
                control_signals.append(0)  # No enviar señal de control
            else:
                all_motors_reached_setpoint = False  # Si al menos un motor no ha llegado, no se detiene todo el control

                # Control PID
                proportional = params['Kp'] * error

                params['integral'] += error * self.dt
                integral = params['Ki'] * params['integral']
                integral = max(min(integral, 100), -100)  # Anti-windup

                derivative = params['Kd'] * ((error - params['previous_error']) / self.dt)

                # Señal de control final
                control_signal = proportional + integral + derivative

                # Asegurar límites de PWM
                pwm_min, pwm_max = (-32000, 32000) if motor == "motor1" else (-60, 60)
                control_signal = max(min(control_signal, pwm_max), pwm_min)

                # Guardar señal de control
                control_signals.append(int(control_signal))

                # Actualizar error anterior
                params['previous_error'] = error

        if abs(self.motor_params['motor1']['setpoint'] - self.motor_params['motor1']['measured_angle']) >= self.error_margin:
            self.motor1_control_msg.data = control_signals[0]
            self.control1_pub.publish(self.motor1_control_msg)
        
        if abs(self.motor_params['motor2']['setpoint'] - self.motor_params['motor2']['measured_angle']) >= self.error_margin:
            self.motor2_control_msg.data = control_signals[1]
            self.control2_pub.publish(self.motor2_control_msg)

        if all_motors_reached_setpoint:
            self.get_logger().info("Ambos motores alcanzaron el setpoint. Desactivando control.")
            self.control_active = False


def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()