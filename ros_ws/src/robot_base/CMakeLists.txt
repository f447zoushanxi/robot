cmake_minimum_required(VERSION 3.8)
project(robot_base)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_library(serial_interface_stub src/serial_interface_stub.cpp)
target_include_directories(serial_interface_stub PUBLIC include)
add_library(base_safety_utils src/safety_utils.cpp)
target_include_directories(base_safety_utils PUBLIC include)
ament_target_dependencies(base_safety_utils geometry_msgs)

add_executable(base_driver_node src/base_driver_node.cpp)
target_include_directories(base_driver_node PUBLIC include)
ament_target_dependencies(base_driver_node rclcpp geometry_msgs nav_msgs std_msgs)
target_link_libraries(base_driver_node serial_interface_stub base_safety_utils)

install(TARGETS base_driver_node serial_interface_stub base_safety_utils
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/
  DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_timeout_brake test/test_timeout_brake.cpp)
  if(TARGET test_timeout_brake)
    target_link_libraries(test_timeout_brake base_safety_utils)
    target_include_directories(test_timeout_brake PUBLIC include)
  endif()
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
