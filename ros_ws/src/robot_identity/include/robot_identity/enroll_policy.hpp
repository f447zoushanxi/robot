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
// 模块说明：robot_identity — 注册策略声明（enroll_policy.hpp）
// =============================================================================
// 这个头文件声明了主人注册策略的函数接口。
//
// 详细说明见 enroll_policy.cpp。
// =============================================================================

#pragma once

namespace robot_identity
{

// allow_enroll：判断是否允许注册主人
// 参数 owner_enrolled                ：当前是否已有主人注册
// 参数 require_button_for_first_enroll：配置是否要求物理按钮确认
// 参数 request_requires_physical_confirm：本次请求是否要求物理确认
// 返回值：true = 允许，false = 拒绝
bool allow_enroll(
  bool owner_enrolled,
  bool require_button_for_first_enroll,
  bool request_requires_physical_confirm);

}  // namespace robot_identity
