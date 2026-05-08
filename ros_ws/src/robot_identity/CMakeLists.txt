cmake_minimum_required(VERSION 3.8)
project(robot_identity)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(robot_msgs REQUIRED)

add_library(identity_enroll_policy src/enroll_policy.cpp)
target_include_directories(identity_enroll_policy PUBLIC include)

add_executable(identity_node src/identity_node.cpp)
target_include_directories(identity_node PUBLIC include)
ament_target_dependencies(identity_node rclcpp std_msgs std_srvs robot_msgs)
target_link_libraries(identity_node identity_enroll_policy)

install(TARGETS identity_node identity_enroll_policy DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_enroll_gating test/test_enroll_gating.cpp)
  if(TARGET test_enroll_gating)
    target_link_libraries(test_enroll_gating identity_enroll_policy)
    target_include_directories(test_enroll_gating PUBLIC include)
  endif()
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
