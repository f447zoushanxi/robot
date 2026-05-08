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
// 模块说明：robot_base — 安全工具函数（safety_utils）
// =============================================================================
// 这个文件实现"超时刹车"功能。
//
// 背景知识：
//   机器人底盘收不到速度指令时，如果继续按上次指令跑，可能撞墙或伤人。
//   因此需要一个"超时保护"机制：超过一定时间没收到新指令，就强制停车。
//
// apply_timeout_brake 函数：
//   - 输入：最新速度指令 + 是否已超时
//   - 输出：安全速度指令（超时则清零，否则原样返回）
// =============================================================================

#include "robot_base/safety_utils.hpp"

namespace robot_base
{

// apply_timeout_brake：超时刹车函数
// 参数 input   ：上一次收到的速度指令（线速度 + 角速度）
// 参数 timeout ：是否已超过超时门限（true = 超时，需要刹车）
// 返回值       ：安全速度指令（超时时线速度和角速度都清零）
geometry_msgs::msg::Twist apply_timeout_brake(const geometry_msgs::msg::Twist & input, bool timeout)
{
  // 先把输入复制到输出，默认原样返回（未超时时）
  auto output = input;
  if (timeout) {
    // 超时：强制停车——线速度和角速度清零，机器人立刻停止移动
    output.linear.x = 0.0;   // 前进/后退速度清零（单位：米/秒）
    output.angular.z = 0.0;  // 旋转速度清零（单位：弧度/秒）
  }
  return output;
}

}  // namespace robot_base
