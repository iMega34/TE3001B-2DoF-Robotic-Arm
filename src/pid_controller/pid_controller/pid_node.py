#!/usr/bin/env python3

##
 # pid_node.py
 #
 #  Created on: March 3, 2025
 #      Author: @sofiaariasv
##

import rclpy
from rclpy.node import Node
import numpy as np
from std_msgs.msg import Float64MultiArray

class PIDControllerNode(Node):
    def __init__(self):
        super().__init__('pid_controller_node')

        # Matrices de ganancias (Kp, Ki, Kd)
        self.Kp = np.array([[0.55273, 0.1], [0.1, 0.55273]])  
        self.Ki = np.array([[0.30508, 0.05], [0.05, 0.30508]])
        self.Kd = np.array([[0.05222, 0.01], [0.01, 0.05222]])

        # Resolución del encoder (pulsos por revolución)
        self.encoder_resolution = 312  # Cambia este valor según tu encoder

        # Setpoint y valor medido
        self.setpoint = np.array([0.0, 0.0])  # Setpoint inicial en ángulos (grados)
        self.measured_value = np.array([0.0, 0.0])  # Valor medido inicial en pulsos

        # Variables del PID
        self.previous_error = np.array([0.0, 0.0])
        self.integral = np.array([0.0, 0.0])
        self.dt = 0.1  # Intervalo de tiempo (en segundos)

        # Margen de error para detener el controlador (en pulsos)
        self.error_margin = 1  

        # Bandera para habilitar/deshabilitar el control
        self.control_active = True

        # Subscriptor para el valor medido (posición en pulsos)
        self.encoder_sub = self.create_subscription(
            Float64MultiArray,  
            '/current_pulses',   
            self.encoder_callback,
            10
        )

        # Subscriptor para el setpoint (posición en ángulos)
        self.setpoint_sub = self.create_subscription(
            Float64MultiArray, 
            '/desired_angle',  
            self.setpoint_callback,
            10
        )

        # Publicador para la señal de control
        self.control_pub = self.create_publisher(
            Float64MultiArray,  
            '/control_law',   
            10
        )

        # Timer para el bucle de control
        self.timer = self.create_timer(self.dt, self.control_loop)

    def encoder_callback(self, msg):
        # Actualizar el valor medido (posición en pulsos)
        self.measured_value = np.array(msg.data)
        # Convertir la posición medida a ángulos
        measured_angle = self.pulses_to_angle(self.measured_value)
        # Imprimir la posición medida en pulsos y ángulos
        self.get_logger().info(f"Posición medida: {self.measured_value} pulsos ({measured_angle} grados)")

    def setpoint_callback(self, msg):
        # Actualizar el setpoint (posición en ángulos)
        self.setpoint = np.array(msg.data)

        # Convertir el setpoint de ángulos a pulsos
        self.setpoint = self.angle_to_pulses(self.setpoint)
        self.get_logger().info(f"Setpoint actualizado: {self.setpoint} pulsos")

        # Reiniciar la bandera de control cuando se actualiza el setpoint
        self.control_active = True

    def control_loop(self):
        if not self.control_active:
            return  

        # Calcular el error (en pulsos)
        error = self.setpoint - self.measured_value

        # Verificar si el error está dentro del margen de error
        if np.all(np.abs(error) < self.error_margin):
            self.get_logger().info("Setpoint alcanzado. Deteniendo el controlador.")
            self.control_active = False
            return  

        # Control PID
        proportional = self.Kp @ error

        self.integral += error * self.dt
        integral = self.Ki @ self.integral

        derivative = self.Kd @ ((error - self.previous_error) / self.dt)

        control_signal = proportional + integral + derivative

        control_signal = np.clip(control_signal, -255, 255)

        self.previous_error = error

        # Publicar la señal de control
        control_msg = Float64MultiArray()
        control_msg.data = control_signal.tolist()
        self.control_pub.publish(control_msg)

        self.get_logger().info(f"Señal de control enviada: {control_msg.data}")

    def angle_to_pulses(self, angle):
        return angle * (self.encoder_resolution / 360.0)

    def pulses_to_angle(self, pulses):
        return pulses * (360.0 / self.encoder_resolution)

def main(args=None):
    rclpy.init(args=args)
    node = PIDControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()