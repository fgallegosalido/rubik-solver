#include <iostream>
#include <string>
#include "cube.hpp"
#include "old_pochmann_solver.hpp"
#include "utilities.hpp"

int main(){
    Cube c;
    OldPochmannSolver solver{c};
    std::string t;

    while(true){
        std::cout << c << std::endl;

        std::cout << "Type a valid sequence of turns --> ";
        std::getline(std::cin, t);

        if (t == "q" || t == "quit")
            break;
        else if (t == "s" || t == "solve")
            solver.solve();
        else {
            c << t;
        }
    }
}
