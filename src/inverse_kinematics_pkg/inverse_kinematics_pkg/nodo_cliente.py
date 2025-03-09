#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from desired_position_pkg.srv import DesiredPosition

class NodoCliente(Node):
    def __init__(self):
        super().__init__('nodo_cliente')
        self.cli = self.create_client(DesiredPosition, 'desired_position')

        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Esperando el servicio...')

    def send_request(self, x, y):
        req = DesiredPosition.Request()
        req.x = int(x)
        req.y = int(y)
        future = self.cli.call_async(req)
        rclpy.spin_until_future_complete(self, future)
        return future.result()

def main(args=None):
    rclpy.init(args=args)
    cliente = NodoCliente()

    try:
        x = int(input("Ingrese x: "))  # Coordenada x
        y = int(input("Ingrese y: "))  # Coordenada y

        # Enviar solicitud al servidor
        response = cliente.send_request(x, y)

        if response.theta1 != -1.0 and response.theta2 != -1.0:
            cliente.get_logger().info(f"Ángulos recibidos: theta1={response.theta1}, theta2={response.theta2}")
        else:
            cliente.get_logger().info("Posición no alcanzable.")
    except ValueError:
        cliente.get_logger().error("Ingrese valores numéricos válidos.")
    finally:
        cliente.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()