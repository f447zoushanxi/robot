// Copyright 2026 f447zoushanxi
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

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
