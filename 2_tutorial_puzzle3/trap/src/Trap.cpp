#include "Trap.h"
#include <numeric>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/log/trivial.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>

namespace qi = boost::spirit::qi;

BOOST_FUSION_ADAPT_STRUCT(Scale, (int, id)(std::vector<Int>, left_side)(std::vector<Int>, right_side))

template<typename Iterator>
struct weight_parser : qi::grammar<Iterator, Scale(), qi::blank_type> {
    weight_parser() : weight_parser::base_type(scale){
        using namespace qi;
        elem = *ulong_long;
        scale = int_ >> ": " >> elem >> "- " >> elem;
    }
    qi::rule<Iterator, Scale(), qi::blank_type> scale;
    qi::rule<Iterator, std::vector<Int>(), qi::blank_type> elem;
};

bool Trap::Init(const std::string& trap_log){
    auto first_it = trap_log.begin(), last_it = trap_log.end();
    weight_parser<std::string::const_iterator> p;
    bool ok = qi::phrase_parse(first_it, last_it, p, qi::blank, scale_);
    return first_it == last_it;
}

bool check_weight_diversity(const Scale& scale)
{
    std::unordered_map<Int, int> weight_count;
    for (const auto& weight : scale.left_side){
        ++weight_count[weight];
        if (weight_count[weight] > 1) return false;
    }
    for (const auto& weight : scale.right_side){
        ++weight_count[weight];
        if (weight_count[weight] > 1) return false;
    }
    return true;
}


bool check_weight_equility(const Scale& scale){
    if(scale.left_side.size() != scale.right_side.size()) return false;
    boost::multiprecision::cpp_int lcm_all = 1;
    for (const auto& weight : scale.left_side){
        if(weight <= 0){
            BOOST_LOG_TRIVIAL(debug) << "error checking, scale id: " << scale.id << 
                " wrong weight: " << weight << "\n";
            return false;
        }
        lcm_all = boost::math::lcm(lcm_all, weight);
    }
    for (const auto& weight : scale.right_side){
        if(weight <= 0){
            BOOST_LOG_TRIVIAL(debug) << "error checking, scale id: " << scale.id << 
                " wrong weight: " << weight << "\n";
            return false;
        }
        lcm_all = boost::math::lcm(lcm_all, weight);
    }
    boost::multiprecision::cpp_int sum_left = 0, sum_right = 0;
    for (const auto& weight : scale.left_side){
        sum_left += lcm_all/weight;
    }
    for (const auto& weight : scale.right_side){
        sum_right += lcm_all/weight;
    }
    bool res = sum_left == sum_right;
    if(res){
        BOOST_LOG_TRIVIAL(debug) << ": " << scale.id << 
        " lcm_all: " << lcm_all << 
        " sum_right: " << sum_right <<
        " sum_left: " << sum_left <<
        "\n";
    }
    return res;
}

bool Trap::Check(){
    return check_weight_diversity(scale_) && 
           check_weight_equility(scale_);
}
