from setuptools import find_packages, setup

package_name = 'inverse_kinematics_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='sofia',
    maintainer_email='sofia@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'inverse_kinematics_servidor = inverse_kinematics_pkg.nodo_servidor:main',
            'inverse_kinematics_cliente = inverse_kinematics_pkg.nodo_cliente:main',
        ],
    },
)
