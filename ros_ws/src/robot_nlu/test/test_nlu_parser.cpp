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
