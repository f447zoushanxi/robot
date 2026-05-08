// Copyright (c) 2026.
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

#include <gtest/gtest.h>

#include "robot_nlu/nlu_parser.hpp"

TEST(NluParser, ParseDeliverWaterIntent)
{
  const auto json = robot_nlu::parse_to_json("请给我递水");
  EXPECT_NE(json.find("\"intent\":\"deliver_water\""), std::string::npos);
}

TEST(NluParser, ParseStopIntent)
{
  const auto json = robot_nlu::parse_to_json("立刻停下");
  EXPECT_NE(json.find("\"intent\":\"stop\""), std::string::npos);
}
