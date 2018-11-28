#include <iostream>
#include <string>
#include "cube.hpp"

int main(){
    Cube c;
    std::string t;

    while(true){
        std::cout << c << std::endl;

        std::cout << "Type a valid sequence of turns --> ";
        std::getline(std::cin, t);

        if (t == "q" || t == "quit")
            break;

        c.read_algorithm(t);
    }
}
