#include "Trap.h"
#include <iostream>
#include <charconv>
#include <string_view>

bool Trap::ParseId(const std::string& trap_log, int& id, std::string::const_iterator& digit_separator_it){
    //parse first digit in the line
    auto begin_digit_it = trap_log.begin();
    while(!std::isdigit(*begin_digit_it) && begin_digit_it!=trap_log.end()){
        begin_digit_it++;
    }
    //parse id separator
    digit_separator_it = begin_digit_it;
    while(*digit_separator_it!=':' && digit_separator_it!=trap_log.end()){
        digit_separator_it++;
    }
    auto result = std::from_chars(&(*begin_digit_it), &(*digit_separator_it), id);
    return result.ec != std::errc::invalid_argument;
}

void Trap::AnalyseStatus(const std::string& trap_log, const std::string::const_iterator& digit_separator_it){
    auto log_reverse_it = trap_log.rbegin();
    bool change_status = true;
    unsigned int count_changes = 0;
    status_ = TrapStatus::kUndefined;
    //Parsing status is started from the end. The number of changed status is counted till finding
    //activated or deactivated status, so the current status is identified.
    while((log_reverse_it.base() - 1) != digit_separator_it && change_status){
        //parse one status, the separator between them is ' ' 
        size_t size = 0;
        while(*log_reverse_it != ' ' && (log_reverse_it.base() - 1) != digit_separator_it){
            log_reverse_it++;
            size++;
        }
        auto parsed_status = std::string_view(&(*(log_reverse_it.base())), size);
        //check the parsed status is relevant to which category
        if(kDeactivatedStatus.contains(parsed_status)){
            change_status = false;
            if(count_changes % 2 == 0){
                status_ = TrapStatus::kDeactivated;
            }else{
                status_ = TrapStatus::kActivated;
            }
        }else if(kActivatedStatus.contains(parsed_status)){
            change_status = false;
            if(count_changes % 2 == 0){
                status_ = TrapStatus::kActivated;
            }else{
                status_ = TrapStatus::kDeactivated;
            }
        }else if(kChangedStatus.contains(parsed_status)) {
            count_changes++;
        }//else ignore   
        //Jump the ' ' char for separation between status     
        if((log_reverse_it.base() - 1) != digit_separator_it) log_reverse_it++;
    }
}

const std::unordered_set<std::string_view> Trap::kDeactivatedStatus = {"inactive", "disabled", "quiet", "standby", "idle"};
const std::unordered_set<std::string_view> Trap::kActivatedStatus = {"live", "armed", "ready", "primed", "active"};
const std::unordered_set<std::string_view> Trap::kChangedStatus = {"flipped", "toggled", "reversed", "inverted", "switched"};

void Trap::Init(const std::string& trap_log){
    std::string::const_iterator digit_separator_it;
    if(!ParseId(trap_log, id_, digit_separator_it)){
        std::cout<<"ParseId is not successfull, please check the trap_log input!";
    }
    AnalyseStatus(trap_log, digit_separator_it);
}