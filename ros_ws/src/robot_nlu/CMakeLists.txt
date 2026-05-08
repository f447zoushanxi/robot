cmake_minimum_required(VERSION 3.8)
project(robot_nlu)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_library(nlu_parser src/nlu_parser.cpp)
target_include_directories(nlu_parser PUBLIC include)

add_executable(nlu_node src/nlu_node.cpp)
target_include_directories(nlu_node PUBLIC include)
ament_target_dependencies(nlu_node rclcpp std_msgs)
target_link_libraries(nlu_node nlu_parser)

install(TARGETS nlu_node nlu_parser DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_nlu_parser test/test_nlu_parser.cpp)
  if(TARGET test_nlu_parser)
    target_link_libraries(test_nlu_parser nlu_parser)
    target_include_directories(test_nlu_parser PUBLIC include)
  endif()
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
