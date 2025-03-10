#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from desired_position_pkg.srv import DesiredPosition
import math

class CinematicaInversa(Node):
    def __init__(self):
        super().__init__('nodo_cinematica')

        # Longitudes de los eslabones
        self.L1 = 7.5  # Longitud del primer eslabón
        self.L2 = 9.5  # Longitud del segundo eslabón

        # Crear el servicio
        self.srv = self.create_service(DesiredPosition, 'desired_position', self.ik_callback)

        self.get_logger().info("Nodo de Cinemática Inversa Listo.")

    def ik_callback(self, request, response):
        x, y = request.x, request.y

        # Restricción: El efector final no puede estar bajo la mesa (y < 0)
        if y < 0:
            self.get_logger().info("Error: El efector final no puede estar bajo la mesa (y < 0).")
            response.theta1 = int(-1)
            response.theta2 = int(-1)
            return response

        # Calcular la distancia radial
        distancia = math.sqrt(x**2 + y**2)
        R_max = self.L1 + self.L2
        R_min = abs(self.L1 - self.L2)

        # Verificar si el punto está más allá del alcance máximo
        if distancia > R_max or distancia<R_min:
            self.get_logger().info(f"Error: El punto ({x}, {y}) está más allá del alcance máximo.")
            response.theta1 = int(-1)
            response.theta2 = int(-1)
            return response

        # Calcular cinemática inversa
        theta1, theta2 = self.calculate_inverse_kinematics(x, y)
        theta1=int(theta1)
        theta2=int(theta2)

            # Verificar si no hay solución
        if theta1 is None or theta2 is None:
            self.get_logger().info("Error: No hay solución para la cinemática inversa.")
            response.theta1 = int(-1)  # Usar -1 como valor de error
            response.theta2 = int(-1)  # Usar -1 como valor de error
            return response

        # Verificar si los ángulos causan que el efector final pase por debajo de la mesa
        if self.efector_final_debajo_de_la_mesa(theta1, theta2):
            self.get_logger().info("Error: Los ángulos causan que el efector final pase por debajo de la mesa.")
            response.theta1 = int(-1)
            response.theta2 = int(-1)
            return response

        # Si todas las restricciones se cumplen, la posición es alcanzable
        response.theta1 = int(theta1)
        response.theta2 = int(theta2)

        self.get_logger().info(f"Ángulos calculados: theta1={theta1}, theta2={theta2}")
        return response

    def calculate_inverse_kinematics(self, x, y):
        # Calcular la distancia radial
        r = math.sqrt(x**2 + y**2)

        # Verificar si el punto está dentro del workspace
        if r > (self.L1 + self.L2) or r < abs(self.L1 - self.L2):
            return None, None  # No hay solución real

        # Calcular theta2 usando la ley de cosenos
        cos_theta2 = (r**2 - self.L1**2 - self.L2**2) / (2 * self.L1 * self.L2)
        if abs(cos_theta2) > 1:
            return None, None  # Valor fuera del dominio de arccos

        theta2_d = math.acos(cos_theta2)

        # Calcular theta1 usando trigonometría
        alpha = math.atan2(y, x)
        beta = math.acos((r**2 + self.L1**2 - self.L2**2) / (2 * r * self.L1))
        theta1_d = alpha - beta  # Usar alpha - beta para evitar el reflejo

        # Convertir a grados
        theta1 = math.degrees(theta1_d)
        theta2 = math.degrees(theta2_d)

        # Ajustar theta1 para que el home sea vertical (parado)
        theta1 = 90-theta1   # Rotar 90° para que theta1=0° apunte hacia arriba

        # Verificar restricciones del eslabón 1 (theta1 debe estar entre -90° y 90°)
        if theta1 < -90 or theta1 > 90:
            return None, None  # Solución no válida

        return theta1, theta2

    def efector_final_debajo_de_la_mesa(self, theta1, theta2):
        # Calcular la posición del efector final
        theta1_rad = math.radians(theta1)  # Ajustar theta1 para la nueva convención
        theta2_rad = math.radians(theta2)

        x1 = self.L1 * math.sin(theta1_rad)  # Primer eslabón apunta hacia el eje Y+
        y1 = self.L1 * math.cos(theta1_rad)

        x2 = x1 + self.L2 * math.sin(theta1_rad + theta2_rad)
        y2 = y1 + self.L2 * math.cos(theta1_rad + theta2_rad)

        # Verificar si el efector final está por debajo de la mesa
        return y2 < 0

def main(args=None):
    rclpy.init(args=args)
    node = CinematicaInversa()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()