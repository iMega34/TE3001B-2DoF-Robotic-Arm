#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import numpy as np
from std_msgs.msg import Float64MultiArray

class PIDControlNode(Node):
    def __init__(self):
        super().__init__('pid_control_node')

        # Matrices de ganancias con interacción
        self.Kp = np.array([[0.55273,   0.1], 
                            [0.1,       0.55273]])  
        self.Ki = np.array([[0.30508,   0.05], 
                            [0.05,      0.30508]])  
        self.Kd = np.array([[0.05222,   0.01], 
                            [0.01,      0.05222]])  

        # Setpoint inicial
        self.setpoint = np.array([0.0, 0.0])

        # Estado actual de los motores 
        self.measured_value = np.array([0.0, 0.0])

        # Variables para el control PID
        self.previous_error = np.array([0.0, 0.0])
        self.integral = np.array([0.0, 0.0])
        self.dt = 0.1  # Intervalo de tiempo

        # Subscriber para leer los encoders
        self.encoder_sub = self.create_subscription(
            Float64MultiArray,  
            '/joint_states',   
            self.encoder_callback,
            10
        )

        # Subscriber para recibir el setpoint 
        self.setpoint_sub = self.create_subscription(
            Float64MultiArray, 
            '/valid_setpoint', 
            self.setpoint_callback,
            10
        )

        # Publisher para enviar la señal de control
        self.control_pub = self.create_publisher(
            Float64MultiArray,  
            '/control_law',   
            10
        )

        # Timer para calcular y publicar la señal de control periódicamente
        self.timer = self.create_timer(self.dt, self.control_loop)  # Frecuencia de 10 Hz

    def encoder_callback(self, msg):
        # Actualizar el estado actual de los motores
        self.measured_value = np.array(msg.data)
        self.get_logger().info(f"Valor medido: {self.measured_value}")

    def setpoint_callback(self, msg):
        # Actualizar el setpoint validado por la cinemática inversa
        self.setpoint = np.array(msg.data)
        self.get_logger().info(f"Setpoint actualizado: {self.setpoint}")

    def control_loop(self):
        # Calcular el error
        error = self.setpoint - self.measured_value

        # Término proporcional
        proportional = self.Kp @ error

        # Término integral
        self.integral += error * self.dt
        integral = self.Ki @ self.integral

        # Término derivativo
        derivative = self.Kd @ ((error - self.previous_error) / self.dt)

        # Calcular PID
        control_signal = proportional + integral + derivative

        # Actualizar el error anterior
        self.previous_error = error

        # Publicar la señal de control
        control_msg = Float64MultiArray()
        control_msg.data = control_signal.tolist()
        self.control_pub.publish(control_msg)

        # Log para depuración
        self.get_logger().info(f"Señal de control enviada: {control_msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = PIDControlNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()