cmake_minimum_required(VERSION 3.8)
project(robot_voice)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(voice_bridge_node src/voice_bridge_node.cpp)
ament_target_dependencies(voice_bridge_node rclcpp std_msgs)

install(TARGETS voice_bridge_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
