# TE3001B-2DoF-Robotic-Arm

## Objective:
The objective of the project is to design and implement a 2-DOF (Degrees of Freedom) robotic arm controlled using micro-ROS and ROS 2. The system will leverage micro-ROS for communication between the          hardware (motors and sensors) and ROS 2 for high-level processing, including inverse kinematics calculations and PID control.

## ROS Arquitecture
The ROS 2 architecture starts with a node that requests a service for the desired position. The inverse kinematics server checks whether the desired position is feasible and sends a response if it is valid. Within the inverse kinematics server, there is a publisher that sends the calculated desired joint positions to a topic called desired joint. Another node, called the PID controller, subscribes to both the joint state and desired joint topics. After computing the control law, the PID controller node publishes the results to a topic called control law.
On the Arduino platform, there are two nodes. The first node, the Kalman filter, reads the encoder values and estimates the joint velocity and position vectors. It then publishes this information to a topic named joint state. The second node, called motor drive, subscribes to the control law topic and applies specific PWM voltage signals to the motors.

![image](https://github.com/user-attachments/assets/925ca901-834a-43d4-ab77-66d2342f2d9b)

## Robotic arm
Degrees of Freedom (DOF): 2 (cylindrical joints).

Length of the Links:

  - Lower Link (L1): 7.5 cm.

  - Upper Link (L2): 9.5 cm.

Material: 3D-printed components (PLA).

Motors: DC motors with included encoder (GM 25-370 Motor with Encoder 12V DC 140RPM / 330RPM).

![image](https://github.com/user-attachments/assets/ef27cec1-42bc-4b06-8a6f-34d0f88312b6)

## PID 
#### PID of lower link
Kp: 0.55273

Ki: 0.20

Kd: 0.0

![image](https://github.com/user-attachments/assets/750e767a-38b8-43fd-8f11-993ec7741c08)

#### PID of Upper link
Kp: 0.50

Ki: 0.20

Kd: 0.0

![image](https://github.com/user-attachments/assets/7cf6db67-9735-4ca8-94a2-fbbe1621cea2)

#### Video
Clic here to watch the video [aquí](https://drive.google.com/file/d/1GGvGxa0Eim0qaEbZwvnnj2Kc3X7D-hnp/view?usp=sharing).

## Inverse Kinematics
#### Robot workspace

Lower Limit: Table surface (y = 0).

Upper Limit: Maximum reach of the arm (y = L1 + L2 = 17 cm).

Lateral Limits of lower link: Defined by the joint angles (-90° to 90°).

![image](https://github.com/user-attachments/assets/4d60d083-45c5-400b-a631-2533c408297b)

## Results of the PID
The robotic arm is already reaching its target position, but there are a few things we need to fine-tune to make it run more smoothly and accurately. Here’s a breakdown of what we’ve noticed:

#### Oscillations in Motor 2 (Upper Link):
The motor for the upper link tends to oscillate, which makes the movement less stable than it should be. This tells us that we need to tweak the PID control to improve the motor’s response and prevent overshooting.

#### Structural Issues with Motor 2:
The motor for the upper link sometimes drifts ("sweeps"), which suggests there might be a problem with the mechanical structure or how the control is implemented. This needs to be checked to avoid incorrect movements.

#### Motor Noise:
We’re working on implementing a Kalman filter to reduce noise in the encoder measurements. This will help us achieve more precise control and prevent jerky or inaccurate movements.

## Commands to run the project
To flash the ESP32 use PlatformIO as the toolchain.
#### Run the micro-ROS agent:
This command starts the micro-ROS agent to enable communication between the ESP32 and ROS 2.

    ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0 -b 115200    
#### Run the PID controller node:
This command starts the PID control node for the robotic arm.

    ros2 run pid_controller pid_control_node
#### Run the inverse_kinematics_servive:
    ros2 run inverse_kinematics_pkg inverse_kinematics_servidor
#### Run the inverse_kinematics_client:
    ros2 run inverse_kinematics_pkg inverse_kinematics_cliente







