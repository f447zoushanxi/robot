#include "robot_nav/location_manager.hpp"

#include <fstream>
#include <regex>

namespace robot_nav
{

bool LocationManager::load_from_yaml(const std::string & file_path)
{
  std::ifstream ifs(file_path);
  if (!ifs.is_open()) {
    return false;
  }

  // 这里用轻量级正则读取 {name: xxx, x: 0.0, y: 0.0, yaw: 0.0} 行。
  // 真实项目建议用 yaml-cpp 完整解析并做字段校验。
  const std::regex line_pattern(
    R"(\{name:\s*([^,]+),\s*x:\s*([\-0-9\.]+),\s*y:\s*([\-0-9\.]+),\s*yaw:\s*([\-0-9\.]+)\})");

  std::string line;
  std::smatch match;
  while (std::getline(ifs, line)) {
    if (std::regex_search(line, match, line_pattern) && match.size() == 5) {
      NamedLocation loc;
      loc.name = match[1].str();
      loc.name.erase(0, loc.name.find_first_not_of(" \t"));
      loc.name.erase(loc.name.find_last_not_of(" \t") + 1);
      loc.x = std::stod(match[2].str());
      loc.y = std::stod(match[3].str());
      loc.yaw = std::stod(match[4].str());
      locations_[loc.name] = loc;
    }
  }
  return !locations_.empty();
}

bool LocationManager::has(const std::string & key) const
{
  return locations_.find(key) != locations_.end();
}

NamedLocation LocationManager::get(const std::string & key) const
{
  auto it = locations_.find(key);
  if (it != locations_.end()) {
    return it->second;
  }
  return NamedLocation{};
}

}  // namespace robot_nav
