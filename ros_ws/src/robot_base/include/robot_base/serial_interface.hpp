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
// 模块说明：robot_base — 串口接口（serial_interface.hpp）
// =============================================================================
// 这个头文件定义了"底盘串口通信"的数据结构和接口。
//
// 背景知识：
//   真实的移动底盘（轮子电机驱动板）通常通过串口（USB 转串口）与电脑通信。
//   电脑发送速度指令，底盘回传编码器数据（左右轮走了多少格）和急停状态。
//
//   VelocityCommand ：电脑 → 底盘，告诉底盘该走多快、转多快。
//   BaseFeedback    ：底盘 → 电脑，报告编码器计数和急停按钮状态。
//   SerialInterface ：纯虚基类（接口），定义了通信必须支持的操作。
//
// 为什么用"接口"（纯虚类）？
//   这样可以有不同的实现：StubSerialInterface（测试用，假装有底盘）和
//   RealSerialInterface（真实底盘）。切换只需要换一行代码，其他地方不用改。
// =============================================================================

#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace robot_base
{

// VelocityCommand：发给底盘的速度指令
// vx_mps  ：前进速度，单位 米/秒（正值前进，负值后退）
// wz_rps  ：旋转速度，单位 弧度/秒（正值逆时针，负值顺时针）
// enable  ：使能信号，false 表示电机断电/停止
struct VelocityCommand
{
  double vx_mps{0.0};
  double wz_rps{0.0};
  bool enable{true};
};

// BaseFeedback：底盘反馈给电脑的数据
// left_ticks  ：左轮编码器计数（每圈多少格，驱动板配置决定）
// right_ticks ：右轮编码器计数
// estop       ：急停按钮是否被按下（true = 按下 = 必须停车）
struct BaseFeedback
{
  int32_t left_ticks{0};
  int32_t right_ticks{0};
  bool estop{false};
};

// SerialInterface：串口通信接口（纯虚基类）
// 定义了任何底盘驱动实现都必须支持的三个操作：
//   open()          ：打开串口（例如 "/dev/ttyUSB0", 115200 baud）
//   write_command() ：向底盘发送速度指令
//   read_feedback() ：从底盘读取编码器/急停反馈（无数据时返回空 optional）
class SerialInterface
{
public:
  virtual ~SerialInterface() = default;

  // 打开串口，port 例如 "/dev/ttyUSB0"，baudrate 例如 115200
  virtual bool open(const std::string & port, int baudrate) = 0;

  // 向底盘发送速度指令
  virtual bool write_command(const VelocityCommand & cmd) = 0;

  // 从底盘读取编码器反馈（用 std::optional，没有数据时返回空值）
  virtual std::optional<BaseFeedback> read_feedback() = 0;
};

}  // namespace robot_base
