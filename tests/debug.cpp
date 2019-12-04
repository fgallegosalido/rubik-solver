#include <iostream>
#include <string>
#include "cube.hpp"
#include "cross.hpp"
#include "old_pochmann_solver.hpp"

int main(){
    Cube c;
    OldPochmannSolver solver{c};
    Cross cross_solver{c};
    std::string t;

    while(true){
        std::cout << c << std::endl;

        std::cout << "Type a valid sequence of turns --> ";
        std::getline(std::cin, t);

        if (t == "q" || t == "quit")
            break;

        if (t == "s" || t == "solve")
            solver.solve();
        else if (t == "c" || t == "cross")
            std::cout << cross_solver.solve() << std::endl;
        else
            c << t;
    }
}
