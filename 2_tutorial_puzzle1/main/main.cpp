#include <fstream>
#include "RecipeChecker.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

void init_log_filter(){
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}

int main(int argc, char* argv[])
{
    try 
    {
        init_log_filter();
        
        std::ifstream data_library;
        data_library.open(PROJECT_PATH "/configs/11_keymaker_recipe.txt");

        if(!data_library.is_open()) {
            perror("Error opening the data library file!");
            exit(EXIT_FAILURE);
        }
        std::string recipe_checker_log;
        while(std::getline(data_library, recipe_checker_log)) {
            BOOST_LOG_TRIVIAL(trace) << recipe_checker_log << "\n";
            RecipeChecker recipe_checker;
            recipe_checker.Init(recipe_checker_log);
            auto key = recipe_checker.Check();
            if(key){
                BOOST_LOG_TRIVIAL(info) << "Key found, it is: " << key.value();
                return 0;
            }
        }
        BOOST_LOG_TRIVIAL(info) << "Key not found !";
        return 0;
    }
    catch(std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << e.what() << "\n";
    }
}