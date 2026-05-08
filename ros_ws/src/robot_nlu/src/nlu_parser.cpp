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

#include "robot_nlu/nlu_parser.hpp"

namespace robot_nlu
{

std::string parse_to_json(const std::string & text)
{
  // 规则优先：保证高频家庭指令无需依赖大模型也能稳定运行。
  if (text.find("停") != std::string::npos) {
    return
      "{\"intent\":\"stop\",\"slots\":{},"
      "\"auth\":{\"requested_role\":\"any\",\"require_confirmation\":false}}";
  }
  if (text.find("记住我的声音") != std::string::npos) {
    return
      "{\"intent\":\"enroll_owner_voice\",\"slots\":{},"
      "\"auth\":{\"requested_role\":\"owner\",\"require_confirmation\":true}}";
  }
  if (text.find("记住我") != std::string::npos) {
    return
      "{\"intent\":\"enroll_owner\",\"slots\":{},"
      "\"auth\":{\"requested_role\":\"owner\",\"require_confirmation\":true}}";
  }
  if (text.find("我在") != std::string::npos) {
    return
      "{\"intent\":\"remember_location\",\"slots\":{\"user_location\":\"unknown\"},"
      "\"auth\":{\"requested_role\":\"owner\",\"require_confirmation\":false}}";
  }
  if (text.find("去") != std::string::npos) {
    return
      "{\"intent\":\"navigate\",\"slots\":{\"target\":\"living_room\"},"
      "\"auth\":{\"requested_role\":\"guest\",\"require_confirmation\":false}}";
  }
  if (text.find("递水") != std::string::npos || text.find("拿水") != std::string::npos) {
    return
      "{\"intent\":\"deliver_water\",\"slots\":{\"object\":\"bottle\","
      "\"deliver_to\":\"person_nearby\"},"
      "\"auth\":{\"requested_role\":\"owner\",\"require_confirmation\":true}}";
  }

  // 兜底：真实项目中调用 Ollama HTTP API，并强制其返回结构化 JSON。
  // 此处仅保留接口形态，避免把外部依赖硬编码到骨架中。
  return
    "{\"intent\":\"unknown\",\"slots\":{},"
    "\"auth\":{\"requested_role\":\"guest\",\"require_confirmation\":false},"
    "\"source\":\"ollama_fallback_stub\"}";
}

}  // namespace robot_nlu
