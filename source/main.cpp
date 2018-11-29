#include <iostream>

#include "cube.hpp"
#include "old_pochmann_solver.hpp"
#include "utilities.hpp"

int main(){
    auto scramble = random_scramble();
    Cube c{scramble};

    std::cout << "Random Scramble: " << scramble             << "\n"
              << c << std::endl;

    OldPochmannSolver solver{c};

    std::cout << "\nSolving the cube...\n" << std::endl;
    auto solution = solver.solve();

    std::cout << "Solution: "        << solution             << "\n"
              << "Number of turns: " << turn_count(solution) << "\n"
              << c << std::endl;
}
