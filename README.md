# TE3001B-2DoF-Robotic-Arm

Para correr el paquete de PID:

```bash
colcon build
install/setup.bash
ros2 run pid_controller pid_control_node
```
Para correr el paquete de cinematica inversa
```bash
colcon build
install/setup.bash
ros2  run inverse_kinematics_pkg inverse_kinematics_servidor
ros2  run inverse_kinematics_pkg inverse_kinematics_cliente
```
casos prueba y salida
x=5
y=-3
El efector final no puede estar bajo la mesa (y < 0).

x=20
y=20
El punto (20, 20) está más allá del alcance máximo.

x=1
y=1
El punto (1, 1) está fuera del rango alcanzable.

x=5
y=0
Los ángulos causan que el efector final pase por debajo de la mesa.

x=5
y=5
Ángulos fuera de rango permitido: theta1=..., theta2=..

x=0
y=17
Configuración singular detectada. Ajuste theta2 para evitar pérdida de control.