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
// 测试说明：robot_identity — 注册策略单元测试（test_enroll_gating.cpp）
// =============================================================================
// 这个文件测试 allow_enroll() 函数在不同场景下的行为。
//
// 测试用例：
//   1. FirstEnrollRequiresPhysical：主人未注册 + 需要按钮 + 请求要求确认 → 应拒绝
//   2. AllowWhenPhysicalConfirmNotRequired：主人未注册 + 需要按钮 + 请求不要求 → 应允许
//   3. AllowWhenOwnerAlreadyEnrolled：主人已注册 → 始终允许（无论其他条件）
// =============================================================================

#include <gtest/gtest.h>

#include "robot_identity/enroll_policy.hpp"

// 测试用例 1：首次注册需要物理按钮确认（安全保护生效）
// 场景：没有主人注册过，配置要求按钮，请求也要求物理确认
// 期望：拒绝（因为真实按钮还没被按下）
TEST(EnrollPolicy, FirstEnrollRequiresPhysicalConfirmWhenConfigured)
{
  // 参数：owner_enrolled=false, require_button=true, request_confirms=true
  EXPECT_FALSE(robot_identity::allow_enroll(false, true, true));
}

// 测试用例 2：请求本身不要求物理确认（例如内部系统调用）
// 场景：没有主人注册，配置要求按钮，但本次请求声明"不需要物理确认"
// 期望：允许（适用于内部系统初始化等非用户触发的场景）
TEST(EnrollPolicy, AllowWhenPhysicalConfirmNotRequiredByRequest)
{
  // 参数：owner_enrolled=false, require_button=true, request_confirms=false
  EXPECT_TRUE(robot_identity::allow_enroll(false, true, false));
}

// 测试用例 3：主人已经注册过了
// 场景：已有主人，即使需要按钮且请求要求确认，也直接允许（可以更新信息）
// 期望：允许（第一条件满足，直接返回 true）
TEST(EnrollPolicy, AllowWhenOwnerAlreadyEnrolled)
{
  // 参数：owner_enrolled=true（其他参数不影响结果）
  EXPECT_TRUE(robot_identity::allow_enroll(true, true, true));
}
