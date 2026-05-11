# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# robot_perception 包安装配置（setup.py）
# =============================================================================
# 这个文件告诉 Python/ROS2 如何安装 robot_perception 包。
#
# 关键配置说明：
#   - packages：Python 包列表（'robot_perception' 对应同名目录）
#   - data_files：安装时需要复制的非 Python 文件（package.xml 和 ament_index 资源）
#   - entry_points / console_scripts：注册可执行命令
#       'perception_node' 对应 robot_perception.perception_node:main
#       安装后可通过 `ros2 run robot_perception perception_node` 启动
# =============================================================================

from setuptools import setup

package_name = 'robot_perception'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        # ament_index 注册：让 ROS2 能发现这个包
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        # 安装 package.xml（包含依赖信息）
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot-dev',
    maintainer_email='dev@example.com',
    description='Perception service skeleton for bottle detection and person finding.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # 格式：'命令名 = 包名.模块名:入口函数名'
            # 安装后执行 `ros2 run robot_perception perception_node` 会调用 main()
            'perception_node = robot_perception.perception_node:main',
        ],
    },
)
