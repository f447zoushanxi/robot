cmake_minimum_required(VERSION 3.5)
project(robot_ai)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_msgs REQUIRED)
find_package(robot_ai_interfaces REQUIRED)

# Optional: enable ONNXRUNTIME integration if user has it available
option(ENABLE_ONNXRUNTIME "Enable C++ ONNXRuntime inference support" OFF)
if(ENABLE_ONNXRUNTIME)
  add_compile_definitions(USE_ONNXRUNTIME)
  message(STATUS "Building with ONNXRuntime support enabled (USE_ONNXRUNTIME)")
endif()

include_directories(include)

add_executable(lifecycle_node src/lifecycle_node.cpp src/onnx_wrapper.cpp)
ament_target_dependencies(lifecycle_node rclcpp rclcpp_lifecycle std_msgs robot_ai_interfaces)

install(TARGETS
  lifecycle_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
