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

## Inverse Kinematics
#### Robot workspace

Lower Limit: Table surface (y = 0).

Upper Limit: Maximum reach of the arm (y = L1 + L2 = 17 cm).

Lateral Limits of lower link: Defined by the joint angles (-90° to 90°).

![image](https://github.com/user-attachments/assets/4d60d083-45c5-400b-a631-2533c408297b)

## kalman

## Challenge 1
### Ros arquitecture
![image](https://github.com/user-attachments/assets/043b634f-9c7d-4225-942f-7df10a4dd475)

### PID
#### PID of lower link
Kp: 0.55273

Ki: 0.20

Kd: 0.0

![image](https://github.com/user-attachments/assets/18e938d4-4aed-40e4-928e-8bab877510f9)

#### PID of Upper link
Kp: .030

Ki: 0.015

Kd: 0.115

![image](https://github.com/user-attachments/assets/16c938ea-ba36-4163-b49e-76a520cbdffa)

### Inverse Cinematic
#### Formulas
![image](https://github.com/user-attachments/assets/48b678f4-379a-423c-87bb-32d2fca92352)
![image](https://github.com/user-attachments/assets/2ca2cb4a-3ca1-4324-8be6-c8a5d5a77fae)

You input x and y in the terminal.
The Cartesian plane is based on centimeters (cm) because the lengths of the robot's links are given in cm.
In inverse kinematics, the robot's singularities are calculated, as well as its motion limits, and a warning message is displayed when a specific point cannot be reached.

![image](https://github.com/user-attachments/assets/942ddb7d-dbeb-4d73-9a14-3e700fd1558e)

Additionally, a Python simulation is included to visualize how the robot's joints are positioned after applying inverse kinematics.
![image](https://github.com/user-attachments/assets/ddd324ad-dc61-4feb-90e9-04a5916602dc)


### Results of the project
#### Inverse Cinematic
![image](https://github.com/user-attachments/assets/3e566179-7336-45a3-892f-e06e3e0f9df0)
#### Video
Click here to watch the video: [Here](https://drive.google.com/file/d/1HXhLsasoq05iibtM2fsnmvH80p_B4CIg/view?usp=sharing)
#### Result
![image](https://github.com/user-attachments/assets/695f2a44-3a65-41a6-b6a2-a14421e22d41)

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







