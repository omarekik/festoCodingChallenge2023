#pragma once
#include <string>
#include <vector>
#include <utility>
#include <optional>

class RecipeChecker{
private:
    static const std::vector<std::pair<char,std::string>> hammers;
    
public:
    bool Init(const std::string& trap_log);
    std::optional<std::string> Check();

    std::vector<std::pair<int, int>> recipe_;
};

