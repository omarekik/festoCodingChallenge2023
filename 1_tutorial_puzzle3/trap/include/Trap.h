#pragma once
#include <string>
#include <unordered_set>

enum class TrapStatus {kDeactivated=0, kActivated, kUndefined};

class Trap{
private:
    static const std::unordered_set<std::string_view> kDeactivatedStatus;
    static const std::unordered_set<std::string_view> kActivatedStatus;
    static const std::unordered_set<std::string_view> kChangedStatus;

    bool ParseId(const std::string& trap_log, int& id, std::string::const_iterator& id_separator_it);
    void AnalyseStatus(const std::string& trap_log, const std::string::const_iterator& digit_separator_it);
    
public:
    void Init(const std::string& trap_log);
    int id_;
    TrapStatus status_;
};

