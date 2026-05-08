// Copyright (c) 2026.
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

#include "robot_base/serial_interface.hpp"

namespace robot_base
{

class StubSerialInterface : public SerialInterface
{
public:
  bool open(const std::string &, int) override {return true;}
  bool write_command(const VelocityCommand &) override {return true;}
  std::optional<BaseFeedback> read_feedback() override
  {
    return BaseFeedback{};
  }
};

}  // namespace robot_base
