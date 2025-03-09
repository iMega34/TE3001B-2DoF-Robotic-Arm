#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from desired_position_pkg.srv import DesiredPosition
from std_msgs.msg import Int16MultiArray
import math
import numpy as np

class CinematicaInversa(Node):
    def __init__(self):
        super().__init__('nodo_cinematica')

        # Longitudes de los eslabones
        self.L1 = 7.5  # Longitud del primer eslabón
        self.L2 = 9.5  # Longitud del segundo eslabón

        # Crear el servicio
        self.srv = self.create_service(DesiredPosition, 'desired_position', self.ik_callback)

        # Crear el publicador
        self.publisher = self.create_publisher(Int16MultiArray, '/joint_angles', 10)

        self.get_logger().info("Nodo de Cinemática Inversa Listo.")

    def ik_callback(self, request, response):
        msg = Int16MultiArray()
        x, y = request.x, request.y

        # Restricción: El efector final no puede estar bajo la mesa (x < 0)
        if x < 0:
            self.get_logger().info("Error: El efector final no puede estar bajo la mesa (x < 0).")
            response.theta1 = -1
            response.theta2 = -1
            return response

        # Calcular la distancia radial
        distancia = math.sqrt(x**2 + y**2)
        R_max = self.L1 + self.L2

        # Verificar si el punto está más allá del alcance máximo
        if distancia > R_max:
            self.get_logger().info(f"Error: El punto ({x}, {y}) está más allá del alcance máximo.")
            response.theta1 = -1
            response.theta2 = -1
            return response

        # Calcular cinemática inversa
        theta1, theta2 = self.calculate_inverse_kinematics(x, y)
        
        # Convertir los ángulos a enteros
        theta1 = int(theta1)
        theta2 = int(theta2)

        # Verificar restricciones de ángulos
        if theta1 == 90 and theta2 > 0:
            self.get_logger().info("Error: Si theta1 es 90°, theta2 no puede ser positivo.")
            response.theta1 = -1
            response.theta2 = -1
            return response

        if theta2 == 90 and theta1 > 0:
            self.get_logger().info("Error: Si theta2 es 90°, theta1 no puede ser positivo.")
            response.theta1 = -1
            response.theta2 = -1
            return response

        # Verificar rango de theta2
        if not (-180 <= theta2 <= 180):
            self.get_logger().info(f"Error: theta2 fuera de rango permitido: {theta2}")
            response.theta1 = -1
            response.theta2 = -1
            return response

        # Verificar singularidades
        if theta2 == 0 or theta2 == 180:
            self.get_logger().info("Error: Configuración singular detectada. Ajuste theta2 para evitar pérdida de control.")
            response.theta1 = -1
            response.theta2 = -1
            return response

        # Verificar si los valores de theta1 y theta2 están dentro del rango de Int16
        if -32768 <= theta1 <= 32767 and -32768 <= theta2 <= 32767:
            msg.data = [theta1, theta2]
            self.publisher.publish(msg)
            self.get_logger().info(f"Publicado en /joint_angles: {msg.data}")
        else:
            self.get_logger().info(f"Error: Los ángulos {theta1}, {theta2} están fuera del rango permitido.")

        # Si todas las restricciones se cumplen, la posición es alcanzable
        response.theta1 = theta1
        response.theta2 = theta2

        # Publicar en el tópico
        msg = Int16MultiArray()
        msg.data = [theta1, theta2]
        self.publisher.publish(msg)
        self.get_logger().info(f"Publicado en /joint_angles: {msg.data}")

        return response

    def calculate_inverse_kinematics(self, x, y):
        # Calcular la distancia radial
        r = np.sqrt(x**2 + y**2)

        # Verificar si el punto está dentro del workspace
        if r > (self.L1 + self.L2) or r < abs(self.L1 - self.L2):
            return None, None  # No hay solución real

        # Calcular theta2 usando la ley de cosenos
        cos_theta2 = (r**2 - self.L1**2 - self.L2**2) / (2 * self.L1 * self.L2)
        if abs(cos_theta2) > 1:
            return None, None  # Valor fuera del dominio de arccos

        theta2_d = np.arccos(cos_theta2)

        # Calcular theta1 usando trigonometría
        alpha = np.arctan2(y, x)
        beta = np.arccos((r**2 + self.L1**2 - self.L2**2) / (2 * r * self.L1))
        theta1_d = alpha - beta

        # Convertir a grados
        theta1 = np.degrees(theta1_d)
        theta2 = np.degrees(theta2_d)

        return theta1, theta2

def main():
    rclpy.init()
    node = CinematicaInversa()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()