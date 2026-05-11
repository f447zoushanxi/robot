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
// 测试说明：robot_nlu — NLU 解析器单元测试（test_nlu_parser.cpp）
// =============================================================================
// 这个文件测试 parse_to_json() 函数能否正确解析语音文字。
//
// 测试用例：
//   1. ParseDeliverWaterIntent：输入"请给我递水"，输出应包含 deliver_water 意图
//   2. ParseStopIntent        ：输入"立刻停下"，输出应包含 stop 意图
//   3. ParseUnknownIntent     ：输入无法识别文本，输出应包含 unknown 意图
// =============================================================================

#include <gtest/gtest.h>

#include "robot_nlu/nlu_parser.hpp"

// 测试用例 1：解析"递水"指令
// 验证：包含"递水"的语音文字，parse_to_json 应返回 deliver_water 意图
TEST(NluParser, ParseDeliverWaterIntent)
{
  // 调用解析函数（"请给我递水"包含"递水"关键词）
  const auto json = robot_nlu::parse_to_json("请给我递水");

  // 验证：返回的 JSON 字符串中包含 "intent":"deliver_water"
  // EXPECT_NE(pos, npos) 等价于"找到了"（不等于未找到位置）
  EXPECT_NE(json.find("\"intent\":\"deliver_water\""), std::string::npos);
}

// 测试用例 2：解析"停"指令
// 验证：包含"停"的语音文字，parse_to_json 应返回 stop 意图
TEST(NluParser, ParseStopIntent)
{
  // "立刻停下"包含"停"关键词
  const auto json = robot_nlu::parse_to_json("立刻停下");

  // 验证：返回的 JSON 包含 stop 意图
  EXPECT_NE(json.find("\"intent\":\"stop\""), std::string::npos);
}

// 测试用例 3：解析未知指令
// 验证：无关键词文本应走兜底逻辑，返回 unknown 意图
TEST(NluParser, ParseUnknownIntent)
{
  const auto json = robot_nlu::parse_to_json("今天天气真好");
  EXPECT_NE(json.find("\"intent\":\"unknown\""), std::string::npos);
}
