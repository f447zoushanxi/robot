// Minimal ONNX wrapper: compile-time optional real ONNXRuntime support.
// If ENABLE_ONNXRUNTIME is OFF (default), this file provides a lightweight stub
// so CI and environments without ONNXRuntime development headers still build.

#include <string>
#include <vector>
#include <iostream>

#ifdef USE_ONNXRUNTIME
// Actual ONNXRuntime C++ API integration
// To enable: pass -DENABLE_ONNXRUNTIME=ON to CMake and ensure ONNXRuntime headers/libraries
// are available on the system. This is intentionally optional to keep CI simple.
#include <onnxruntime_cxx_api.h>
#endif

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
#ifdef USE_ONNXRUNTIME
    try {
      env_ = std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "robot_ai");
      Ort::SessionOptions session_options;
      // Let the user choose providers at runtime (CUDA if available)
      session_options.SetIntraOpNumThreads(1);
      // Session creation deferred to load() so errors are localized
      std::cerr << "[onnx_wrapper] ONNXRuntime enabled; model path: " << model_path_ << std::endl;
      load();
    } catch (const std::exception & e) {
      std::cerr << "[onnx_wrapper] Failed to initialize ONNXRuntime: " << e.what() << std::endl;
    }
#else
    std::cerr << "[onnx_wrapper] Using stub model for: " << model_path_ << std::endl;
#endif
  }

  bool load()
  {
#ifdef USE_ONNXRUNTIME
    try {
      // Try CUDA first if available
      const std::vector<const char*> providers = Ort::GetAvailableProviders();
      Ort::SessionOptions session_options;
      if (std::find(providers.begin(), providers.end(), "CUDAExecutionProvider") != providers.end()) {
        std::cerr << "[onnx_wrapper] CUDAExecutionProvider is available; attempting to use it" << std::endl;
        session_options.AppendExecutionProvider_CUDA(0);
      }
      session_ = std::make_unique<Ort::Session>(*env_, model_path_.c_str(), session_options);
      return true;
    } catch (const std::exception & e) {
      std::cerr << "[onnx_wrapper] Failed to load ONNX model: " << e.what() << std::endl;
      return false;
    }
#else
    (void)model_path_;
    return true; // stub considered loaded
#endif
  }

  std::vector<Detection> infer(const std::vector<uint8_t> & /*image_bgr*/) {
#ifdef USE_ONNXRUNTIME
    // TODO: implement actual pre/post processing matching exported model
    return {};
#else
    // Return empty detections as stub. Replace with actual inference.
    return {};
#endif
  }

private:
  std::string model_path_;
#ifdef USE_ONNXRUNTIME
  std::unique_ptr<Ort::Env> env_;
  std::unique_ptr<Ort::Session> session_;
#endif
};

} // namespace onnx_wrapper
