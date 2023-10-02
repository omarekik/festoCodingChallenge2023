#include "Solver.h"

bool is_ordered(const std::string& input){
    bool result = true;
    if(!input.empty()){
        auto it_first = input.begin();
        auto it_second = it_first + 1;
        while(result && it_second != input.end()){
            result = *it_first <= *it_second;
            it_first = it_second++;
        }
    }
    return result;
}