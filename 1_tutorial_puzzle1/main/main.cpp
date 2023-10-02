#include <iostream>
#include <fstream>
#include "Solver.h"

int main(int argc, char* argv[])
{
    try 
    {
        std::ifstream data_library;
        data_library.open(PROJECT_PATH "/configs/01_keymaker_ordered.txt");

        if(!data_library.is_open()) {
            perror("Error open");
            exit(EXIT_FAILURE);
        }
        bool searching = true;
        std::string key;
        while(searching && std::getline(data_library, key)) {
            if(is_ordered(key)) {
                std::cout << key << std::endl;
                searching = false;
            }
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}