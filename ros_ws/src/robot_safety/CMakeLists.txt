cmake_minimum_required(VERSION 3.8)
project(robot_safety)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(safety_node src/safety_node.cpp)
ament_target_dependencies(safety_node rclcpp geometry_msgs std_msgs)

install(TARGETS safety_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
