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
// 模块说明：robot_identity — 注册策略实现（enroll_policy.cpp）
// =============================================================================
// 这个文件实现"是否允许注册主人"的判断逻辑。
//
// 为什么要有"注册策略"？
//   注册主人是非常敏感的操作，不能随意触发（比如陌生人对机器人说"记住我"）。
//   因此设计了三个判断条件，只有满足特定组合才允许注册：
//
//   条件 1：如果主人已经注册了（owner_enrolled = true）→ 允许（更新信息）
//   条件 2：如果配置不需要物理按钮（require_button = false）→ 允许（开发/测试模式）
//   条件 3：如果请求本身不要求物理确认（request_requires_physical_confirm = false）→ 允许
//
//   其他情况（主人未注册 + 需要按钮 + 请求要求物理确认）→ 拒绝，等待真实按钮按下
//
// 物理按钮的意义：
//   真实硬件上有一个按钮（接 GPIO 或 MCU）。首次注册主人时，必须在机器人旁边
//   按下这个按钮，才能完成注册。这防止远程或非法注册。
// =============================================================================

#include "robot_identity/enroll_policy.hpp"

namespace robot_identity
{

// allow_enroll：判断是否允许主人注册
// 参数 owner_enrolled                ：当前是否已有主人注册
// 参数 require_button_for_first_enroll：配置层面是否要求物理按钮确认
// 参数 request_requires_physical_confirm：本次注册请求是否要求物理确认
// 返回值：true = 允许注册，false = 拒绝注册
bool allow_enroll(
  bool owner_enrolled,
  bool require_button_for_first_enroll,
  bool request_requires_physical_confirm)
{
  // 条件 1：主人已经注册过了（可以更新信息，不需要再走安全检查）
  if (owner_enrolled) {
    return true;
  }

  // 条件 2：配置层面不要求物理按钮（开发/测试模式）
  if (!require_button_for_first_enroll) {
    return true;
  }

  // 条件 3：本次请求不需要物理确认（例如内部系统调用，不是来自用户语音）
  // 如果 request_requires_physical_confirm = true，说明这是来自用户的请求，
  // 此时主人未注册 + 配置需要按钮 → 必须等真实按钮，返回 false（拒绝）
  return !request_requires_physical_confirm;
}

}  // namespace robot_identity
