cmake_minimum_required(VERSION 3.8)
project(robot_identity)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(robot_msgs REQUIRED)

add_executable(identity_node src/identity_node.cpp)
ament_target_dependencies(identity_node rclcpp std_msgs std_srvs robot_msgs)

install(TARGETS identity_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
