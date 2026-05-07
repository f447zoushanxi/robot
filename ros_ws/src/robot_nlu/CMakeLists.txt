cmake_minimum_required(VERSION 3.8)
project(robot_nlu)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(nlu_node src/nlu_node.cpp)
ament_target_dependencies(nlu_node rclcpp std_msgs)

install(TARGETS nlu_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
