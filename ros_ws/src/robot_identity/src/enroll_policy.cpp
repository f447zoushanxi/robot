// Copyright (c) 2026.
//
// SPDX-License-Identifier: Apache-2.0

#include "robot_identity/enroll_policy.hpp"

namespace robot_identity
{

bool allow_enroll(
  bool owner_enrolled,
  bool require_button_for_first_enroll,
  bool request_requires_physical_confirm)
{
  if (owner_enrolled) {
    return true;
  }
  if (!require_button_for_first_enroll) {
    return true;
  }
  return !request_requires_physical_confirm;
}

}  // namespace robot_identity
