// Minimal ONNX wrapper stub. If ONNX Runtime is available, you can
// add real inference code here. For now this file provides a stable
// API so the package builds without requiring ONNXRuntime development
// files in CI.

#include <string>
#include <vector>
#include <iostream>

namespace onnx_wrapper
{

struct Detection {
  std::string label;
  float confidence;
  float x, y, w, h;
};

class OnnxModel
{
public:
  OnnxModel(const std::string & model_path)
  : model_path_(model_path)
  {
    // In a real build enable ONNXRuntime and load model here.
    std::cerr << "[onnx_wrapper] Using stub model for: " << model_path_ << std::endl;
  }

  std::vector<Detection> infer(const std::vector<uint8_t> & /*image_bgr*/) {
    // Return empty detections as stub. Replace with actual inference.
    return {};
  }

private:
  std::string model_path_;
};

} // namespace onnx_wrapper
