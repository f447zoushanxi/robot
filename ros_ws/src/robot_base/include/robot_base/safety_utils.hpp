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
// 模块说明：robot_base — 安全工具函数声明（safety_utils.hpp）
// =============================================================================
// 这个头文件声明了底盘安全相关的工具函数。
//
// 头文件（.hpp）的作用：
//   就像目录页——列出函数的名字和参数，具体实现在 .cpp 文件里。
//   其他文件 #include 这个头文件后就能"知道"有哪些函数可用。
// =============================================================================

#pragma once

// 引入 Twist 消息类型（包含线速度和角速度）
#include "geometry_msgs/msg/twist.hpp"

namespace robot_base
{

// apply_timeout_brake：超时刹车函数声明
// 详细说明见 safety_utils.cpp
// 参数 input   ：最新速度指令
// 参数 timeout ：是否超时（true = 超时 = 需要刹车）
// 返回值       ：安全速度（超时时清零）
geometry_msgs::msg::Twist apply_timeout_brake(
  const geometry_msgs::msg::Twist & input,
  bool timeout);

}  // namespace robot_base
