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
// 模块说明：robot_nlu — NLU 解析器实现（nlu_parser.cpp）
// =============================================================================
// 这个文件把中文语音文字解析成结构化的 JSON 指令。
//
// 解析策略（分两层）：
//   1) 规则优先（本文件）：对高频家庭指令做关键词匹配，不依赖任何 AI 模型。
//      优点：速度快（微秒级）、不需要网络、100% 可预测。
//      缺点：只能处理预设的指令，不能理解新句式。
//
//   2) AI 兜底（真实项目）：规则无法识别时，调用 Ollama（本地大语言模型）
//      来理解自然语言，并强制要求它返回结构化 JSON。
//      当前骨架只留了接口，不实际调用（避免引入外部依赖）。
//
// 输出 JSON 结构说明：
//   {
//     "intent": "deliver_water",   // 意图：这句话想让机器人做什么
//     "slots": {"object": "bottle"},  // 槽位：指令中的关键信息
//     "auth": {                    // 权限要求
//       "requested_role": "owner",  // 需要 owner（主人）身份才能执行
//       "require_confirmation": true // 是否需要物理按钮确认
//     }
//   }
// =============================================================================

#include "robot_nlu/nlu_parser.hpp"

namespace robot_nlu
{

// parse_to_json：把中文语音文字转换成 JSON 格式的机器人指令
// 参数 text ：语音识别出的中文文字（例如"请给我递水"）
// 返回值   ：JSON 字符串（例如 {"intent":"deliver_water",...}）
std::string parse_to_json(const std::string & text)
{
  // 规则优先：保证高频家庭指令无需依赖大模型也能稳定运行。
  // 关键词匹配顺序很重要——更具体的规则要放在前面，避免被通用规则先匹配到。

  // "停"：最高优先级，任何时候说"停"都立刻停车，不需要主人身份
  if (text.find("停") != std::string::npos) {
    return
      R"({"intent":"stop","slots":{},"auth":{"requested_role":"any","require_confirmation":false}})";
  }

  // "记住我的声音"：声纹注册（需要主人身份 + 物理按钮确认，防止陌生人注册）
  if (text.find("记住我的声音") != std::string::npos) {
    return
      R"({"intent":"enroll_owner_voice","slots":{},"auth":{"requested_role":"owner","require_confirmation":true}})";
  }

  // "记住我"：人脸/综合注册（需要主人身份 + 物理按钮确认）
  // 注意：放在"记住我的声音"后面，避免被提前匹配
  if (text.find("记住我") != std::string::npos) {
    return
      R"({"intent":"enroll_owner","slots":{},"auth":{"requested_role":"owner","require_confirmation":true}})";
  }

  // "我在"：用户告知当前位置（"我在客厅"），帮助机器人规划路径
  if (text.find("我在") != std::string::npos) {
    return
      R"({"intent":"remember_location","slots":{"user_location":"unknown"},"auth":{"requested_role":"owner","require_confirmation":false}})";
  }

  // "去"：导航指令（"去客厅"），访客（guest）也可以使用
  if (text.find("去") != std::string::npos) {
    return
      R"({"intent":"navigate","slots":{"target":"living_room"},"auth":{"requested_role":"guest","require_confirmation":false}})";
  }

  // "递水"/"拿水"：完整的递水任务（需要主人身份 + 确认，防止误触发）
  if (text.find("递水") != std::string::npos || text.find("拿水") != std::string::npos) {
    return
      R"({"intent":"deliver_water","slots":{"object":"bottle","deliver_to":"person_nearby"},"auth":{"requested_role":"owner","require_confirmation":true}})";
  }

  // 兜底：真实项目中调用 Ollama HTTP API，并强制其返回结构化 JSON。
  // 此处仅保留接口形态，避免把外部依赖硬编码到骨架中。
  // source 字段标记这是 AI 兜底返回的结果（方便调试）
  return
    R"({"intent":"unknown","slots":{},"auth":{"requested_role":"guest","require_confirmation":false},"source":"ollama_fallback_stub"})";
}

}  // namespace robot_nlu
