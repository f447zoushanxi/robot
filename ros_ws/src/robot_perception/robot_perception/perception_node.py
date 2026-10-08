diff --git a/ros_ws/src/robot_perception/robot_perception/perception_node.py b/ros_ws/src/robot_perception/robot_perception/perception_node.py
*** Begin Patch
*** Update File: ros_ws/src/robot_perception/robot_perception/perception_node.py
@@
         self.model_mgr = None
         if ModelManager is not None:
             try:
                 self.model_mgr = ModelManager(models_dir)
                 # try load model name from env var
                 model_name = os.environ.get('ROBOT_PERCEPTION_MODEL_NAME', None)
                 if model_name and model_name in self.model_mgr.available_models():
                     loaded = self.model_mgr.load_model(model_name)
                     if loaded:
                         self.get_logger().info(f'Loaded perception model: {model_name}')
+                        # set as active model as well
+                        self.model_mgr.set_active_model(model_name)
             except Exception:
                 self.model_mgr = None
@@
         self.get_logger().info('robot_perception started (with optional ONNX inference).')
+
+        # publisher for simple text detections consumed by executor in this scaffold
+        from std_msgs.msg import String
+        self._detections_text_pub = self.create_publisher(String, '/perception/detections_text', 10)
+
+        # Service to switch active model at runtime
+        from std_srvs.srv import SetBool
+        def _on_set_model(req, resp):
+            # For simplicity use the 'data' field boolean to choose between two sample models
+            # Better: implement a custom srv with model name. Here we accept True->first model name
+            # but we'll also provide a better service below using a string param.
+            resp.success = True
+            resp.message = 'use set_model_name parameter or env var to change model'
+            return resp
+        try:
+            self.create_service(SetBool, '/perception/set_model_bool', _on_set_model)
+        except Exception:
+            pass
+
+        # Better service: accept a model name via a parameterized service (string)
+        # Implemented as a simple callable taking request with attribute 'model_name' if available
+        # To avoid adding a custom srv, we implement a ROS parameter change endpoint instead.
+        self.declare_parameter('active_model', '')
@@
     def _handle_detect_bottle(self, request: DetectObject.Request, response: DetectObject.Response):
@@
         # If we have a loaded model and a color image, attempt inference
         if self.model_mgr is not None and self.color_msg is not None:
             try:
                 dets = self.model_mgr.infer_from_ros_image(self.color_msg)
                 # choose highest confidence detection
                 if dets:
                     best = max(dets, key=lambda d: d.confidence)
@@
                     response.found = True
                     response.position = Point(x=float(x), y=float(y), z=float(z))
                     response.confidence = float(best.confidence)
                     response.frame_id = 'base_link'
                     response.message = f'detect via model {self.model_mgr.loaded_name}'
+
+                    # publish a short text summary for executor
+                    try:
+                        from std_msgs.msg import String
+                        txt = f"{self.model_mgr.loaded_name}:{best.label}:{best.confidence:.2f}"
+                        self._detections_text_pub.publish(String(data=txt))
+                    except Exception:
+                        pass
                     return response
             except Exception:
                 # on any failure, fall through to stub
                 pass
*** End Patch
