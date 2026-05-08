cmake_minimum_required(VERSION 3.8)
project(robot_executor)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(robot_msgs REQUIRED)

add_executable(executor_node src/executor_node.cpp)
ament_target_dependencies(executor_node
  rclcpp rclcpp_action geometry_msgs std_msgs std_srvs nav2_msgs robot_msgs)

install(TARGETS executor_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
