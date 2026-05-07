#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace robot_base
{

struct VelocityCommand
{
  double vx_mps{0.0};
  double wz_rps{0.0};
  bool enable{true};
};

struct BaseFeedback
{
  int32_t left_ticks{0};
  int32_t right_ticks{0};
  bool estop{false};
};

class SerialInterface
{
public:
  virtual ~SerialInterface() = default;

  virtual bool open(const std::string & port, int baudrate) = 0;
  virtual bool write_command(const VelocityCommand & cmd) = 0;
  virtual std::optional<BaseFeedback> read_feedback() = 0;
};

}  // namespace robot_base
