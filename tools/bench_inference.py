"""
tools/bench_inference.py

Simple benchmarking script for ONNX models using ONNX Runtime.
Runs N warmup + M timed inferences and prints latency statistics.
"""
import argparse
import time
import numpy as np

try:
    import onnxruntime as ort
    import cv2
except Exception:
    ort = None
    cv2 = None


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--model', required=True)
    p.add_argument('--image', required=True)
    p.add_argument('--runs', type=int, default=100)
    p.add_argument('--warmup', type=int, default=10)
    args = p.parse_args()

    if ort is None or cv2 is None:
        print('Requires onnxruntime and opencv-python')
        return
    sess = ort.InferenceSession(args.model, providers=ort.get_available_providers())
    img = cv2.imread(args.image)
    img = cv2.resize(img, (640,640)).astype('float32')/255.0
    inp = np.transpose(img,(2,0,1))[None,:]

    # warmup
    for _ in range(args.warmup):
        sess.run(None, {sess.get_inputs()[0].name: inp})
    times = []
    for _ in range(args.runs):
        t0 = time.time()
        sess.run(None, {sess.get_inputs()[0].name: inp})
        t1 = time.time()
        times.append((t1-t0)*1000)
    import statistics
    print('runs=', args.runs)
    print('avg ms=', statistics.mean(times))
    print('p95 ms=', np.percentile(times,95))
    print('min ms=', min(times), 'max ms=', max(times))

if __name__ == '__main__':
    main()
