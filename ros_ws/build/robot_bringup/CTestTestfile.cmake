# CMake generated Testfile for 
# Source directory: /ws/ros_ws/src/robot_bringup
# Build directory: /ws/ros_ws/build/robot_bringup
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_dev_mode.launch.test.py "/usr/bin/python3" "-u" "/opt/ros/humble/share/ament_cmake_test/cmake/run_test.py" "/ws/ros_ws/build/robot_bringup/test_results/robot_bringup/test_dev_mode.launch.test.py.xunit.xml" "--package-name" "robot_bringup" "--output-file" "/ws/ros_ws/build/robot_bringup/launch_test/test_dev_mode.launch.test.py.txt" "--command" "/usr/bin/python3" "-m" "launch_testing.launch_test" "/ws/ros_ws/src/robot_bringup/test/dev_mode.launch.test.py" "--junit-xml=/ws/ros_ws/build/robot_bringup/test_results/robot_bringup/test_dev_mode.launch.test.py.xunit.xml" "--package-name=robot_bringup")
set_tests_properties(test_dev_mode.launch.test.py PROPERTIES  LABELS "launch_test" TIMEOUT "120" WORKING_DIRECTORY "/ws/ros_ws/build/robot_bringup" _BACKTRACE_TRIPLES "/opt/ros/humble/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/humble/share/launch_testing_ament_cmake/cmake/add_launch_test.cmake;131;ament_add_test;/ws/ros_ws/src/robot_bringup/CMakeLists.txt;11;add_launch_test;/ws/ros_ws/src/robot_bringup/CMakeLists.txt;0;")
