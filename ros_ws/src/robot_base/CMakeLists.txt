cmake_minimum_required(VERSION 3.8)
project(robot_base)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_library(serial_interface_stub src/serial_interface_stub.cpp)
target_include_directories(serial_interface_stub PUBLIC include)

add_executable(base_driver_node src/base_driver_node.cpp)
target_include_directories(base_driver_node PUBLIC include)
ament_target_dependencies(base_driver_node rclcpp geometry_msgs nav_msgs std_msgs)
target_link_libraries(base_driver_node serial_interface_stub)

install(TARGETS base_driver_node serial_interface_stub
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/
  DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
