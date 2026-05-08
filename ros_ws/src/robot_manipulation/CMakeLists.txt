cmake_minimum_required(VERSION 3.8)
project(robot_manipulation)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(manipulation_node src/manipulation_node.cpp)
ament_target_dependencies(manipulation_node rclcpp std_srvs)

install(TARGETS manipulation_node DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
