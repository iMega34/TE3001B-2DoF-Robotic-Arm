#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from cinematica_inversa_pkg.srv import DesiredPosition
from std_msgs.msg import Float64MultiArray
import math

class CinematicaInversa(Node):
    def __init__(self):
        super().__init__('nodo_cinematica')

        # Longitudes de los eslabones
        self.L1 = 7.5  # Longitud del primer eslabón
        self.L2 = 9.5  # Longitud del segundo eslabón

        # Crear el servicio
        self.srv = self.create_service(DesiredPosition, 'desired_position', self.ik_callback)

        #Crear el publicador
        self.publisher = self.create_publisher(Float64MultiArray, '/joint_angles', 10)

        self.get_logger().info("Nodo de Cinemática Inversa Listo.")

    def ik_callback(self, request, response):
        x, y = request.x, request.y

        # Calcular cinemática inversa usando el modelo algebraico
        theta1, theta2 = self.calculate_inverse_kinematics(x, y)

#Restricciones
#Restricción1: Comprobar si la posición está en el rango de los eslabones
        distancia = math.sqrt(x**2 + y**2)
        if distancia < abs(self.L1 - self.L2) or distancia > (self.L1 + self.L2):
            self.get_logger().info(f"Posición ({x}, {y}) fuera del rango alcanzable.")
            response.theta1 = -1
            response.theta2 = -1
            return response

#Cálculo de los ángulos theta1 y theta2 (cinemática inversa de un brazo de 2DOF)
        cos_theta2 = (x**2 + y**2 - self.L1**2 - self.L2**2) / (2 * self.L1 * self.L2)

        if abs(cos_theta2) > 1:
            self.get_logger().info(f"Posición ({x}, {y}) no es alcanzable debido a valores de cos_theta2 fuera de rango.")
            response.theta1 = -1
            response.theta2 = -1
            return response

        theta2 = math.degrees(math.acos(cos_theta2))
        theta1 = math.degrees(math.atan2(y, x) - math.atan2(self.L2 * math.sin(math.radians(theta2)), self.L1 + self.L2 * math.cos(math.radians(theta2))))

#Restricción 2: Si theta1 o theta2 están fuera del rango [-90, 90]
        if not (-90 <= theta1 <= 90) or not (-90 <= theta2 <= 90):
            self.get_logger().info(f"Ángulos fuera de rango: theta1={theta1}, theta2={theta2}")
            response.theta1 = -1
            response.theta2 = -1
            return response

#Restricción 3: Si ambos ángulos son ±90° y del mismo signo, no es alcanzable
        if abs(theta1) == 90 and abs(theta2) == 90 and (theta1 * theta2 > 0):
            self.get_logger().info(f"Configuración inválida: theta1={theta1}, theta2={theta2} con mismo signo.")
            response.theta1 = float(-1)
            response.theta2 = float(-1)
            return response

#Si todas las restricciones se cumplen, la posición es alcanzable
        response.theta1 = theta1
        response.theta2 = theta2

        # Publicar en el tópico
        msg = Float64MultiArray()
        msg.data = [theta1, theta2]
        self.publisher.publish(msg)
        self.get_logger().info(f"Publicado en /joint_angles: {msg.data}")

        return response

#--------------------------------------
    def calculate_inverse_kinematics(self, x, y):
        # Calcular theta2 usando el modelo algebraico
        cos_theta2 = (x**2 + y**2 - self.L1**2 - self.L2**2) / (2 * self.L1 * self.L2)
        cos_theta2 = max(min(cos_theta2, 1), -1)  # Asegurar que esté en el rango [-1, 1]
        theta2 = math.acos(cos_theta2)  # Solución positiva (configuración "arriba")
        # theta2 = -math.acos(cos_theta2)  # Solución negativa (configuración "abajo")

        # Calcular theta1 usando el modelo algebraico
        alpha = math.atan2(y, x)
        beta = math.atan2(self.L2 * math.sin(theta2), self.L1 + self.L2 * math.cos(theta2))
        theta1 = alpha - beta

        return theta1, theta2

def main():
    rclpy.init()
    node = CinematicaInversa()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
