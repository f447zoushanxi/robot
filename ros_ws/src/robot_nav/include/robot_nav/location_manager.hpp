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
