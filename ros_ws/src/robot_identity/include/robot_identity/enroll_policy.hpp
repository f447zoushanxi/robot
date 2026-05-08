#pragma once

namespace robot_identity
{

bool allow_enroll(
  bool owner_enrolled,
  bool require_button_for_first_enroll,
  bool request_requires_physical_confirm);

}  // namespace robot_identity
