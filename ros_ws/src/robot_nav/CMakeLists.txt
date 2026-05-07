cmake_minimum_required(VERSION 3.8)
project(robot_nav)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(nav_server_node src/nav_server_node.cpp src/location_manager.cpp)
target_include_directories(nav_server_node PUBLIC include)
ament_target_dependencies(nav_server_node rclcpp std_srvs)

install(TARGETS nav_server_node DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
