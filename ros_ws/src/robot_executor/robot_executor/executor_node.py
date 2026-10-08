*** Begin Patch
*** Update File: ros_ws/src/robot_executor/robot_executor/executor_node.py
@@
 class ExecutorNode(Node):
     def __init__(self):
         super().__init__('executor_node')
         self.state = 'idle'
         self.last_detection: Optional[str] = None
         # subscribe to a texty detection topic to keep code simple for now
         self.create_subscription(String, '/perception/detections_text', self._on_detection, 10)
         self.create_service(Trigger, '/executor/get_status', self._handle_get_status)
         self.get_logger().info('executor_node started')
@@
     def _on_detection(self, msg: String):
         self.get_logger().info(f'received detection: {msg.data}')
         self.last_detection = msg.data
         # simple state transition
-        self.state = 'received_detection'
+        # upon detection, verify owner (if identity service available)
+        try:
+            # call identity service to verify owner (stub)
+            client = self.create_client(Trigger, '/robot_identity/verify_owner')
+            if client.wait_for_service(timeout_sec=1.0):
+                req = Trigger.Request()
+                future = client.call_async(req)
+                rclpy.spin_until_future_complete(self, future, timeout_sec=2.0)
+                if future.done() and future.result() is not None and future.result().success:
+                    self.get_logger().info('identity verified: owner')
+                    self.state = 'confirmed_owner'
+                else:
+                    self.state = 'received_detection'
+            else:
+                self.state = 'received_detection'
+        except Exception:
+            self.state = 'received_detection'
*** End Patch
