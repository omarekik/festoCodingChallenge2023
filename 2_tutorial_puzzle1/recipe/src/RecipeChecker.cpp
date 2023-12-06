#include "RecipeChecker.h"
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/log/trivial.hpp>

const std::vector<std::pair<char,std::string>> RecipeChecker::hammers = {
    {'A' , "BC"}, // 1
    {'A' , "CB"}, // 2
    {'B' , "DD"}, // 3
    {'B' , "BD"}, // 4
    {'C' , "CD"}, // 5
    {'C' , "FE"}, // 6
    {'D' , "AF"}, // 7
    {'D' , "FA"}  // 8
};

bool RecipeChecker::Init(const std::string& trap_log){
    namespace x3 = boost::spirit::x3;
    using x3::int_;
    using x3::phrase_parse;
    using x3::_attr;
    using x3::ascii::space;
    auto first_it = trap_log.begin(), last_it = trap_log.end();
    bool res = phrase_parse(first_it, last_it,
        //Begin grammar
        ((
            '(' >> int_ >> ',' >> int_ >> ')'
        ) % '-'),
        //End grammar
        space, recipe_
    );
    if(first_it != last_it) res = false;
    return res;
}

std::optional<std::string> RecipeChecker::Check(){
    std::string key="A";
    for(auto instruction : recipe_){ 
        auto [hammer_index, position] = instruction;
        if(hammer_index > RecipeChecker::hammers.size()){
            BOOST_LOG_TRIVIAL(trace)<<"hammer_index, position = " << hammer_index << " , " << position << "\n";
            return {};
        } 
        hammer_index--;
        auto [hammer_input_char, hammer_output_2chars] = RecipeChecker::hammers[hammer_index];
        if(key.size() >= position && 
           key[position - 1] == hammer_input_char){
            key[position - 1] = hammer_output_2chars[0];
            key.insert(position, 1, hammer_output_2chars[1]);
        }else{
            BOOST_LOG_TRIVIAL(trace)<<"hammer_index, position = " << hammer_index << " , " << position << "\n";
            BOOST_LOG_TRIVIAL(trace)<<"hammer_input_char, hammer_output_2chars = " << hammer_input_char << " , " << hammer_output_2chars << "\n";
            BOOST_LOG_TRIVIAL(trace)<<"key[position - 1], key = " << key[position - 1] << " , " << key << "\n";
            return {};
        } 
    }
    return key;
}