#include <gtest/gtest.h>

#include "robot_identity/enroll_policy.hpp"

TEST(EnrollPolicy, FirstEnrollRequiresPhysicalConfirmWhenConfigured)
{
  EXPECT_FALSE(robot_identity::allow_enroll(false, true, true));
}

TEST(EnrollPolicy, AllowWhenPhysicalConfirmNotRequiredByRequest)
{
  EXPECT_TRUE(robot_identity::allow_enroll(false, true, false));
}

TEST(EnrollPolicy, AllowWhenOwnerAlreadyEnrolled)
{
  EXPECT_TRUE(robot_identity::allow_enroll(true, true, true));
}
