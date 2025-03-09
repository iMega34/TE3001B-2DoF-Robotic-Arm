import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/sofia/sextoSem/TE3001B-2DoF-Robotic-Arm/install/inverse_kinematics_pkg'
