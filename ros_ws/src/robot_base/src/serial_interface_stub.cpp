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

// =============================================================================
// 模块说明：robot_base — 串口接口模拟实现（serial_interface_stub）
// =============================================================================
// 这个文件实现了"假底盘"（Stub）——所有操作都假装成功，但不真正驱动硬件。
//
// 什么是 Stub（占位/模拟实现）？
//   当我们还没有真实底盘、或者在电脑上测试代码时，不能让代码因为"找不到串口"
//   而崩溃。Stub 提供了一个假实现：open() 直接返回 true，write_command() 直接
//   返回 true，read_feedback() 返回空的反馈数据（编码器清零，急停为 false）。
//
// 使用方法：
//   当 use_stub=true 时，底盘节点使用 StubSerialInterface 而不是真实串口实现。
//   真实项目里，切换只需要把 StubSerialInterface 替换成 RealSerialInterface。
// =============================================================================

#include "robot_base/serial_interface.hpp"

namespace robot_base
{

// StubSerialInterface：串口通信的模拟实现（假底盘）
// 继承 SerialInterface 接口，但所有操作都是"假的"
class StubSerialInterface : public SerialInterface
{
public:
  // open：假装打开串口，直接返回 true（成功）
  bool open(const std::string &, int) override {return true;}

  // write_command：假装发送速度指令，直接返回 true（成功）
  bool write_command(const VelocityCommand &) override {return true;}

  // read_feedback：假装从底盘读取数据，返回一个空反馈（所有字段为默认值）
  // BaseFeedback{} 等价于 {left_ticks=0, right_ticks=0, estop=false}
  std::optional<BaseFeedback> read_feedback() override
  {
    return BaseFeedback{};
  }
};

}  // namespace robot_base
