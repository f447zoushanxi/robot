# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

from setuptools import setup

package_name = 'robot_sim'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot-dev',
    maintainer_email='dev@example.com',
    description='Pure-software simulation nodes for the home robot.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'fake_scan_node = robot_sim.fake_scan_node:main',
        ],
    },
)
