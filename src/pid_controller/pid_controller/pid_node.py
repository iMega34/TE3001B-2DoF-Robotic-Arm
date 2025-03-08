#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Int16MultiArray

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller')

        # Parámetros independientes para cada motor
        self.motor_params = {
            'motor1': {
                'Kp': 0.55273,  # Ganancia proporcional
                'Ki': 0.20,  # Ganancia integral
                'Kd': 0.0,      # Ganancia derivativa
                'setpoint': 0.0,  # Setpoint en grados
                'measured_angle': 0.0,  # Valor medido en grados
                'previous_error': 0.0,  # Error anterior
                'integral': 0.0,  # Término integral acumulado
            },
            'motor2': {
                'Kp': 0.5527,  # Ganancia proporcional
                'Ki': 0.20,  # Ganancia integral
                'Kd': 0.0,  # Ganancia derivativa
                'setpoint': 90.0,  # Setpoint en grados
                'measured_angle': 0.0,  # Valor medido en grados
                'previous_error': 0.0,  # Error anterior
                'integral': 0.0,  # Término integral acumulado
            }
        }

        # Intervalo de tiempo (en segundos)
        self.dt = 0.5

        # Margen de error para detener el controlador (en grados)
        self.error_margin = 1.0

        # Bandera para habilitar/deshabilitar el control
        self.control_active = True

        # Subscriptor para el valor medido (posición en grados)
        self.encoder_sub = self.create_subscription(
            Int16MultiArray,
            '/encoders',
            self.encoder_callback,
            5
        )

        # Subscriptor para el setpoint (posición en grados)
        self.setpoint_sub = self.create_subscription(
            Int16MultiArray,
            '/desired_joint',
            self.setpoint_callback,
            5
        )

        # Publicador para la señal de control
        self.control_pub = self.create_publisher(
            Int16MultiArray,
            '/control_law',
            10
        )

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop)

        # Crear el mensaje de control una sola vez
        self.control_msg = Int16MultiArray()

    def encoder_callback(self, msg):
        # Actualizar los valores medidos (posición en grados) para cada motor
        if len(msg.data) >= 2:
            self.motor_params['motor1']['measured_angle'] = float(msg.data[0])
            self.motor_params['motor2']['measured_angle'] = float(msg.data[1])

            # Mostrar en el log
            for motor in ['motor1', 'motor2']:
                self.get_logger().info(
                    f"{motor}: Posición medida = {self.motor_params[motor]['measured_angle']} grados")

    def setpoint_callback(self, msg):
        # Actualizar los setpoints (posición en grados) para cada motor
        if len(msg.data) >= 2:
            self.motor_params['motor1']['setpoint'] = float(msg.data[0])
            self.motor_params['motor2']['setpoint'] = float(msg.data[1])

            # Mostrar en el log
            for motor in ['motor1', 'motor2']:
                self.get_logger().info(
                    f"{motor}: Setpoint actualizado = {self.motor_params[motor]['setpoint']} grados")

            # Reiniciar la bandera de control cuando se actualiza el setpoint
            self.control_active = True

    def control_loop(self):
        if not self.control_active:
            return

        # Calcular la señal de control para cada motor
        control_signals = []
        for motor in ['motor1', 'motor2']:
            params = self.motor_params[motor]

            # Calcular el error (en grados)
            error = params['setpoint'] - params['measured_angle']

            # Verificar si el error está dentro del margen de error
            if abs(error) < self.error_margin:
                self.get_logger().info(f"{motor}: Setpoint alcanzado.")
                control_signals.append(0)  # No enviar señal de control
                self.control_active = False
                continue

            # Control PID
            proportional = params['Kp'] * error
            params['integral'] += error * self.dt
            integral = params['Ki'] * params['integral']
            derivative = params['Kd'] * ((error - params['previous_error']) / self.dt)

            # Señal de control
            control_signal = proportional + integral + derivative

            # Asegurarse de que la señal de control esté en el rango de PWM
            pwm_min, pwm_max = (-60, 60)
            control_signal = max(min(control_signal, pwm_max), pwm_min)

            # Actualizar el error anterior
            params['previous_error'] = error

            # Agregar la señal de control a la lista
            control_signals.append(int(control_signal))

        # Publicar las señales de control
        self.control_msg.data = control_signals
        self.control_pub.publish(self.control_msg)

        # self.get_logger().info(f"Señales de control enviadas: {control_signals}", throttle_duration_sec=1)

def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()