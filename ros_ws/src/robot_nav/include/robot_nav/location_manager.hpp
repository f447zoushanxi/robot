// Copyright (c) 2026.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <map>
#include <string>

namespace robot_nav
{

struct NamedLocation
{
  std::string name;
  double x{0.0};
  double y{0.0};
  double yaw{0.0};
};

class LocationManager
{
public:
  bool load_from_yaml(const std::string & file_path);
  bool has(const std::string & key) const;
  NamedLocation get(const std::string & key) const;

private:
  std::map<std::string, NamedLocation> locations_;
};

}  // namespace robot_nav
