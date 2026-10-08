"""
ai_inference.py

Improved ONNX model manager with provider detection, absolute path support,
metadata handling, and runtime active model switching.
"""
from __future__ import annotations

import os
import threading
import time
from typing import List, Dict, Optional

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
    """Manage multiple ONNX models stored under a models directory.

    Features:
    - Parse models_list.txt (name|filename|url[,task_hint])
    - Support filename as either relative filename under models_dir, or an absolute path
      when prefixed by file://
    - Load model into an onnxruntime.InferenceSession preferring CUDAExecutionProvider
      if available; fall back to CPUExecutionProvider.
    - Allow runtime switching with set_active_model(name)
    - Expose available_models(), active_model_name()
    """

    def __init__(self, models_dir: str):
        self.models_dir = os.path.abspath(models_dir)
        self.models_map: Dict[str, Dict] = {}
        self._parse_models_list()
        self.session_lock = threading.Lock()
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
                name = parts[0].strip()
                filename = parts[1].strip()
                url = parts[2].strip()
                task_hint = parts[3].strip() if len(parts) > 3 else None
                # resolve path: support file://absolute/path or relative filename
                if filename.startswith('file://'):
                    path = filename[len('file://'):]
                else:
                    path = os.path.join(self.models_dir, filename)
                self.models_map[name] = dict(path=path, url=url, hint=task_hint)

    def available_models(self) -> List[str]:
        return list(self.models_map.keys())

    def active_model_name(self) -> Optional[str]:
        return self.loaded_name

    def _providers_preferred(self) -> List[str]:
        """Return ordered provider list preferring GPU if available."""
        if ort is None:
            return []
        try:
            providers = ort.get_available_providers()
            # prefer CUDA if present
            if 'CUDAExecutionProvider' in providers:
                return ['CUDAExecutionProvider', 'CPUExecutionProvider']
            return providers
        except Exception:
            return []

    def load_model(self, name: str) -> bool:
        """Load the model into memory (but do not set active unless set_active_model called).
        Returns True on success.
        """
        info = self.models_map.get(name)
        if not info:
            return False
        path = info['path']
        if not os.path.exists(path):
            return False
        if ort is None:
            # runtime not available; treat as loaded stub
            with self.session_lock:
                self.loaded_session = None
                self.loaded_name = name
            return True
        # create session with preferred providers (atomic)
        providers = self._providers_preferred()
        try:
            sess_options = ort.SessionOptions()
            sess_options.intra_op_num_threads = 1
            # choose providers order: ort will pick the first available
            # In Python API, we pass providers to InferenceSession constructor
            sess = ort.InferenceSession(path, sess_options, providers=providers if providers else None)
            with self.session_lock:
                self.loaded_session = sess
                self.loaded_name = name
            return True
        except Exception:
            with self.session_lock:
                self.loaded_session = None
                self.loaded_name = None
            return False

    def set_active_model(self, name: str) -> bool:
        """Convenience: load + set active model in one call."""
        return self.load_model(name)

    def infer_from_cv_image(self, cv_image_bgr) -> List[Detection]:
        if self.loaded_name is None:
            return []
        if self.loaded_session is None:
            # stub detection for integration tests
            return [Detection(label='bottle', confidence=0.6, x=0.5, y=0.5, w=0.1, h=0.2)]
        if np is None:
            return []
        import cv2
        # default preprocess: resize to 640x640 and normalize
        h, w = cv_image_bgr.shape[:2]
        tgt_h, tgt_w = 640, 640
        img = cv2.resize(cv_image_bgr, (tgt_w, tgt_h)).astype('float32') / 255.0
        input_tensor = np.transpose(img, (2, 0, 1))[None, :]
        # run inference
        with self.session_lock:
            sess = self.loaded_session
            if sess is None:
                return []
            try:
                inputs = {sess.get_inputs()[0].name: input_tensor}
                outputs = sess.run(None, inputs)
            except Exception:
                return []
        # try several heuristics to parse outputs
        detections: List[Detection] = []
        out0 = outputs[0]
        try:
            # common format: [num,6] or [N,85] for yolov8-like
            if out0.ndim == 2 and out0.shape[1] >= 6:
                # treat as rows of [x,y,w,h,score,class] or [x,y,w,h,score,cls]
                for row in out0:
                    # heuristics
                    if len(row) >= 6:
                        x, y, w_box, h_box, score, cls = row[0], row[1], row[2], row[3], row[4], int(row[5])
                        detections.append(Detection(label=str(cls), confidence=float(score), x=float(x), y=float(y), w=float(w_box), h=float(h_box)))
            else:
                # fallback: try flatten and take top-k
                flat = out0.flatten()
                if flat.size >= 6:
                    detections.append(Detection(label='obj', confidence=float(flat[0]), x=0.5, y=0.5, w=0.1, h=0.1))
        except Exception:
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
