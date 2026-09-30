"""
ai_inference.py

Lightweight ONNX model manager for robot_perception. Attempts to use onnxruntime
if available. Provides a simple API:
  mgr = ModelManager(models_dir)
  mgr.load_model('deepseek_free')  # load by name from models_list.txt
  detections = mgr.infer_current_image(image_bgr)

This module is intentionally defensive: if onnxruntime or cv_bridge is not
available, it will behave as a stub so the rest of the system continues to run
(e.g., in CI or on machines without GPU).
"""
from __future__ import annotations

import os
from typing import List, Dict, Tuple, Optional

# Optional imports
try:
    import onnxruntime as ort
except Exception:
    ort = None

try:
    import numpy as np
    from cv_bridge import CvBridge
except Exception:
    np = None
    CvBridge = None


class Detection:
    def __init__(self, label: str, confidence: float, x: float, y: float, w: float, h: float):
        self.label = label
        self.confidence = confidence
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def as_dict(self):
        return dict(label=self.label, confidence=self.confidence, x=self.x, y=self.y, w=self.w, h=self.h)


class ModelManager:
    def __init__(self, models_dir: str):
        self.models_dir = models_dir
        self.models_map: Dict[str, str] = {}
        self._parse_models_list()
        self.loaded_session = None
        self.loaded_name: Optional[str] = None
        self.bridge = CvBridge() if CvBridge is not None else None

    def _parse_models_list(self):
        list_file = os.path.join(self.models_dir, 'models_list.txt')
        if not os.path.exists(list_file):
            return
        with open(list_file, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith('#'):
                    continue
                parts = line.split('|')
                if len(parts) < 3:
                    continue
                name, filename, url = parts[0].strip(), parts[1].strip(), parts[2].strip()
                path = os.path.join(self.models_dir, filename)
                self.models_map[name] = path

    def available_models(self) -> List[str]:
        return list(self.models_map.keys())

    def load_model(self, name: str) -> bool:
        path = self.models_map.get(name)
        if not path or not os.path.exists(path):
            return False
        if ort is None:
            # onnxruntime not installed; pretend load succeeded (stub)
            self.loaded_session = None
            self.loaded_name = name
            return True
        # try to create inference session (use default providers; CUDA provider used if available in runtime)
        try:
            sess = ort.InferenceSession(path, providers=ort.get_available_providers())
            self.loaded_session = sess
            self.loaded_name = name
            return True
        except Exception:
            # loading failed
            self.loaded_session = None
            self.loaded_name = None
            return False

    def infer_from_cv_image(self, cv_image_bgr) -> List[Detection]:
        """Run inference on a CV image (BGR numpy array). Returns list of Detection."""
        if self.loaded_name is None:
            return []
        if self.loaded_session is None:
            # stub: return empty or synthetic detection for testing
            return [Detection(label='bottle', confidence=0.6, x=0.4, y=0.4, w=0.1, h=0.2)]

        # NOTE: different models expect different input shapes and pre/post-processing.
        # This generic loader expects models that take a single [N,C,H,W] float32 input
        # in BGR order and output a [num,6] array (label_id, score, x, y, w, h) or similar.
        # Real integration should adapt to chosen models' IO signatures.
        img = cv_image_bgr
        if np is None:
            return []
        # resize to 640x640 as a default
        import cv2

        input_img = cv2.resize(img, (640, 640)).astype('float32') / 255.0
        # HWC -> CHW
        input_tensor = np.transpose(input_img, (2, 0, 1))[None, :]
        # run
        try:
            outputs = self.loaded_session.run(None, {self.loaded_session.get_inputs()[0].name: input_tensor})
        except Exception:
            return []
        # Postprocess: attempt to parse common output shapes
        detections: List[Detection] = []
        # outputs[0] assumed to be [num,6] or similar
        out = outputs[0]
        try:
            for row in out:
                # heuristic: [x, y, w, h, score, class]
                if len(row) >= 6:
                    x, y, w, h, score, cls = row[0], row[1], row[2], row[3], row[4], int(row[5])
                    detections.append(Detection(label=str(cls), confidence=float(score), x=float(x), y=float(y), w=float(w), h=float(h)))
        except Exception:
            # fallback: no parse
            pass
        return detections

    def infer_from_ros_image(self, ros_image) -> List[Detection]:
        if self.bridge is None:
            return []
        try:
            cv_img = self.bridge.imgmsg_to_cv2(ros_image, desired_encoding='bgr8')
        except Exception:
            return []
        return self.infer_from_cv_image(cv_img)
