#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from cinematica_inversa_pkg.srv import DesiredPosition

class ServicioPosicion(Node):
    def __init__(self):
        super().__init__('nodo_servicio')
        self.cli = self.create_client(DesiredPosition, 'desired_position')

        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Esperando el servicio de cinemática inversa...')

    def send_request(self, x, y, z):
        request = DesiredPosition.Request()
        request.x = x
        request.y = y
        request.z = z

        future = self.cli.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        return future.result()

def main():
    rclpy.init()
    node = ServicioPosicion()

    while True:
        try:
            x = float(input("Ingrese x: "))
            y = float(input("Ingrese y: "))
            z = float(input("Ingrese z: "))

            response = node.send_request(x, y, z)

            if response.x != -1 and response.y != -1 and response.z != -1:
                node.get_logger().info(f"Posición alcanzable: ({response.x}, {response.y}, {response.z})")
            else:
                node.get_logger().info("Posición NO alcanzable. Intente nuevamente.")

        except ValueError:
            print("Ingrese valores numéricos.")

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
