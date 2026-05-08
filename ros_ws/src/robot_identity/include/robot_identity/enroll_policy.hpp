// Copyright (c) 2026.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace robot_identity
{

bool allow_enroll(
  bool owner_enrolled,
  bool require_button_for_first_enroll,
  bool request_requires_physical_confirm);

}  // namespace robot_identity
