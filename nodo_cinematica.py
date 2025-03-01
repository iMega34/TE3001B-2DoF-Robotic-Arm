#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from cinematica_inversa_pkg.srv import DesiredPosition
from std_msgs.msg import Float64MultiArray

class CinematicaInversa(Node):
    def __init__(self):
        super().__init__('nodo_cinematica')

        # Crear el servicio
        self.srv = self.create_service(DesiredPosition, 'desired_position', self.ik_callback)

        #Crear el publicador
        self.publisher = self.create_publisher(Float64MultiArray, 'desired_joint', 10)

        self.get_logger().info("Nodo de Cinemática Inversa Listo.")

    def ik_callback(self, request, response):
        x, y, z = request.x, request.y, request.z

        resultado = x**2 + y**2 + z**2  # Fórmula de validación

        if resultado < 20:
            response.x = x
            response.y = y
            response.z = z

            #Publicar
            msg = Float64MultiArray()
            msg.data = [x, y, z]
            self.publisher.publish(msg)
            self.get_logger().info(f"📢 Publicado en /desired_joint: {msg.data}")
        else:
            response.x = -1
            response.y = -1
            response.z = -1
            self.get_logger().info(f"Posición ({x}, {y}, {z}) NO alcanzable. No se publica en /desired_joint.")

        return response

def main():
    rclpy.init()
    node = CinematicaInversa()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
