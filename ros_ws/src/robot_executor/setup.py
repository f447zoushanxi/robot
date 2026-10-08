from setuptools import setup

package_name = 'robot_executor'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    package_dir={'': '.'},
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=False,
    maintainer='robot-dev',
    maintainer_email='dev@example.com',
    description='Minimal executor stub for integration tests',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
            'executor_node = robot_executor.executor_node:main',
        ],
    },
)
