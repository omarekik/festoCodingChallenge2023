#include "Trap.h"
#include <fstream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

void init_log_filter(){
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );
}

int main(int argc, char* argv[])
{
    try 
    {
        init_log_filter();

        std::ifstream data_library;
        data_library.open(PROJECT_PATH "/configs/13_trap_balance.txt");

        if(!data_library.is_open()) {
            perror("Error opening the data library file!");
            exit(EXIT_FAILURE);
        }
        std::string trap_log;
        int sum_ids = 0;
        while(std::getline(data_library, trap_log)) {
            BOOST_LOG_TRIVIAL(trace) << trap_log << "\n";
            Trap trap;
            if(!trap.Init(trap_log)){
                BOOST_LOG_TRIVIAL(debug) << "error parsing: " << trap_log << "\n";
                break;
            }
            if(trap.Check()){
                sum_ids += trap.scale_.id;
                BOOST_LOG_TRIVIAL(debug) << "and the trap_log was: " << trap_log << "\n";
            } 
        }
        BOOST_LOG_TRIVIAL(info) << sum_ids << "\n";
    }
    catch(std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << e.what() << "\n";
    }
}