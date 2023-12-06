#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using Int = unsigned long long int;

struct Scale{
  int id;
  std::vector<Int> left_side;
  std::vector<Int> right_side;
  auto operator<=>(const Scale&) const = default;
};

class Trap{    
public:
    bool Init(const std::string& trap_log);
    bool Check();
    Scale scale_;
};

