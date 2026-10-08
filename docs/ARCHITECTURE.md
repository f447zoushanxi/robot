# Architecture overview for robot AI stack

This document describes the high-level architecture, data flows, and responsibilities of
major components introduced in this PR.

- robot_ai_interfaces: ROS2 message definitions used by perception/executor/planning
- robot_perception: perception nodes (Python) providing services and topics
- robot_ai: C++ lifecycle node(s) and an optional ONNX wrapper (compile-time opt-in)
- robot_executor: simple executor that receives perception outputs and runs task FSMs

Mermaid sequence (high-level):

```mermaid
sequenceDiagram
  participant User
  participant Voice
  participant NLU
  participant Perception
  participant Executor
  participant Robot
  User->>Voice: "请给我递水"
  Voice->>NLU: transcribed text
  NLU->>Executor: intent: deliver_water
  Executor->>Perception: request detect_bottle
  Perception->>Perception: (model) detect -> position
  Perception->>Executor: detection result
  Executor->>Robot: plan & execute pick/place
```

Notes:
- ModelManager implements dynamic loading of ONNX models at runtime and
  falls back to a stub when onnxruntime is not available.
- C++ ONNX integration is optional (ENABLE_ONNXRUNTIME) to avoid forcing heavy
  build dependencies on CI.
