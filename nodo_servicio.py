#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from cinematica_inversa_pkg.srv import DesiredPosition

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

    def send_request(self, x, y):
        request = DesiredPosition.Request()
        request.x = x
        request.y = y

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

            response = node.send_request(x, y)

            if response.theta1 != -1 and response.theta2 != -1:
                node.get_logger().info(f"Ángulos obtenidos: theta1={response.theta1}, theta2={response.theta2}")
            else:
                node.get_logger().info("Posición NO alcanzable. Intente nuevamente.")

        except ValueError:
            print("Ingrese valores numéricos.")

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
