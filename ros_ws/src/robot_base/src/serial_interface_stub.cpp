#include "robot_base/serial_interface.hpp"

namespace robot_base
{

class StubSerialInterface : public SerialInterface
{
public:
  bool open(const std::string &, int) override { return true; }
  bool write_command(const VelocityCommand &) override { return true; }
  std::optional<BaseFeedback> read_feedback() override
  {
    return BaseFeedback{};
  }
};

}  // namespace robot_base
