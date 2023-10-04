#include <iostream>
#include <fstream>
#include "Trap.h"

int main(int argc, char* argv[])
{
    try 
    {
        std::ifstream data_library;
        data_library.open(PROJECT_PATH "/configs/03_trap_logs.txt");

        if(!data_library.is_open()) {
            perror("Error opening the data library file!");
            exit(EXIT_FAILURE);
        }
        std::string trap_log;
        int sum_ids = 0;
        while(std::getline(data_library, trap_log)) {
            Trap trap;
            trap.Init(trap_log);
            if(trap.status_ == TrapStatus::kDeactivated) {
                sum_ids += trap.id_;
            }
        }
        std::cout << sum_ids;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}