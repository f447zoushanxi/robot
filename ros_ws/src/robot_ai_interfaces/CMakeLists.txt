cmake_minimum_required(VERSION 3.8)
project(robot_ai_interfaces)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

install(DIRECTORY include/ DESTINATION include)

ament_package()
