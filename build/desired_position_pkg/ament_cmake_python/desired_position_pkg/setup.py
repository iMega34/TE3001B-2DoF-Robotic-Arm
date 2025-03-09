from setuptools import find_packages
from setuptools import setup

setup(
    name='desired_position_pkg',
    version='0.0.0',
    packages=find_packages(
        include=('desired_position_pkg', 'desired_position_pkg.*')),
)
