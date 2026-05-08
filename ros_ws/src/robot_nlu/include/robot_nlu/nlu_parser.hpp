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
// 模块说明：robot_nlu — NLU 解析器声明（nlu_parser.hpp）
// =============================================================================
// 这个头文件声明了 parse_to_json() 函数的接口。
//
// 使用方法：
//   其他文件 #include "robot_nlu/nlu_parser.hpp" 后，
//   就可以调用 robot_nlu::parse_to_json("请给我递水") 获取 JSON 指令。
// =============================================================================

#pragma once

#include <string>

namespace robot_nlu
{

// parse_to_json：把中文语音文字转换成 JSON 格式的机器人指令
// 参数 text ：语音识别出的中文文字
// 返回值   ：JSON 字符串（包含 intent、slots、auth 字段）
std::string parse_to_json(const std::string & text);

}  // namespace robot_nlu
