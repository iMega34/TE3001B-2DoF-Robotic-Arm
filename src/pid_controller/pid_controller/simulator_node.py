#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray

class SimulatorNode(Node):
    def __init__(self):
        super().__init__('simulator_node')

        # Publicadores para setpoint y encoders
        self.setpoint_pub = self.create_publisher(Float64MultiArray, '/valid_setpoint', 10)
        self.encoder_pub = self.create_publisher(Float64MultiArray, '/joint_states', 10)

        # Timer para publicar mensajes periódicamente
        self.timer = self.create_timer(1.0, self.publish_values)  # Publicar cada 1 segundo

    def publish_values(self):
        # Publicar setpoint
        setpoint_msg = Float64MultiArray()
        setpoint_msg.data = [1.0, 1.0]  # Setpoint deseado
        self.setpoint_pub.publish(setpoint_msg)
        self.get_logger().info(f"Setpoint publicado: {setpoint_msg.data}")

        # Publicar valores de encoders
        encoder_msg = Float64MultiArray()
        encoder_msg.data = [0.5, 0.5]  # Valores simulados de encoders
        self.encoder_pub.publish(encoder_msg)
        self.get_logger().info(f"Encoders publicados: {encoder_msg.data}")

def main(args=None):
    rclpy.init(args=args)
    simulator_node = SimulatorNode()
    rclpy.spin(simulator_node)
    simulator_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()