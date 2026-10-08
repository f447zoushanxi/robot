# Implementation details for the executor FSM and simulation flow

This document describes the FSM implemented in ros_ws/src/robot_executor/robot_executor/executor_node.py
and how to run the simulation helper scripts and tests.

FSM states
- idle: initial state
- locating: waiting for perception to produce a detection
- verifying_identity: call /robot_identity/verify_owner to ensure correct recipient
- approaching: move towards the object
- grasping: attempt to grasp
- transporting: carry object to destination
- placing: place the object
- verifying: check placement
- done: task completed successfully
- fallback / cancelled / error: terminal states for failure or cancellation

How the scaffold ties together
- perception_node publishes a short text summary on /perception/detections_text when a detection occurs
- executor subscribes to that topic and uses it as the trigger to proceed
- identity_node provides a /robot_identity/verify_owner Trigger service (stubbed to always return success)
- start a task with: ros2 service call /executor/start_task std_srvs/srv/Trigger "{}"

Running the simulation helper
- Ensure ROS2 Humble environment is sourced and workspace built
- Run: bash tools/sim_tasks/run_fold_and_collect_sim.sh
- The helper will start the dev_sim bringup, call start_task, publish a detection, and print executor status

Launch test (launch_testing)
- Provided test: tests/integration/launch_test_executor_flow.py
- This test launches dev_sim, starts the executor task and asserts the executor reaches 'done' within timeout
- launch_testing requires a ROS2 test environment; run via rostest/launch_test as appropriate
