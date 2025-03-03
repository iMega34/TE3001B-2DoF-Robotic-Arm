#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
from std_msgs.msg import Float64MultiArray

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller_node')

        # Matrices de ganancias 
        self.Kp = np.array([[0.55273, 0.1], [0.1, 0.55273]])  # Ejemplo para 2 grados de libertad
        self.Ki = np.array([[0.30508, 0.05], [0.05, 0.30508]])
        self.Kd = np.array([[0.05222, 0.01], [0.01, 0.05222]])

        # Setpoint y valor medido 
        self.setpoint = np.array([0.0, 0.0])  # Setpoint inicial
        self.measured_value = np.array([0.0, 0.0])  # Valor medido inicial

        # Variables del PID
        self.previous_error = np.array([0.0, 0.0])
        self.integral = np.array([0.0, 0.0])
        self.dt = 0.1  # Intervalo de tiempo (en segundos)

        # Margen de error 
        self.error_margin = .5

        # Bandera para habilitar/deshabilitar el control
        self.control_active = True

        # Subscriptor para posición actual de los motores
        self.encoder_sub = self.create_subscription(
            Float64MultiArray,  # Tipo de mensaje
            '/joint_states',   # Tópico
            self.encoder_callback,
            10
        )

        # Subscriptor para posición deseada
        self.setpoint_sub = self.create_subscription(
            Float64MultiArray,  # Tipo de mensaje
            '/desired_joint',  # Tópico
            self.setpoint_callback,
            10
        )

        # Publicador para la señal de control
        self.control_pub = self.create_publisher(
            Float64MultiArray,  # Tipo de mensaje
            '/control_law',    # Tópico
            10
        )

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop)

    def encoder_callback(self, msg):
        self.measured_value = np.array(msg.data)
        self.get_logger().info(f"Valor medido: {self.measured_value}")

    def setpoint_callback(self, msg):
        self.setpoint = np.array(msg.data)
        self.get_logger().info(f"Setpoint actualizado: {self.setpoint}")

        # Reiniciar la bandera de control cuando se actualiza el setpoint
        self.control_active = True

    def control_loop(self):
        if not self.control_active:
            return  

        # Calcular el error
        error = self.setpoint - self.measured_value

        # Verificar si el error está dentro del margen de error
        if np.all(np.abs(error) < self.error_margin):
            self.get_logger().info("Setpoint alcanzado. Deteniendo el controlador.")
            self.control_active = False
            return  

        # Analisis de control
        proportional = self.Kp @ error

        self.integral += error * self.dt
        integral = self.Ki @ self.integral

        derivative = self.Kd @ ((error - self.previous_error) / self.dt)

        control_signal = proportional + integral + derivative

        self.previous_error = error

        # Publicar la señal de control
        control_msg = Float64MultiArray()
        control_msg.data = control_signal.tolist()
        self.control_pub.publish(control_msg)

        self.get_logger().info(f"Señal de control enviada: {control_msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()