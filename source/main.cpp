#include <iostream>

#include "cube.hpp"
#include "old_pochmann_blind_solver.hpp"
#include "utilities.hpp"

int main(){
    auto scramble = random_scramble();

    std::cout << "Random Scramble: " << scramble             << "\n"
              << c << std::endl;

    Cube c{scramble};
    OldPochmannBlindSolver solver{c};

    std::cout << "\nSolving the cube using " << solver.name() << "\n" << std::endl;
    auto solution = solver.solve();

    std::cout << "Solution: "        << solution             << "\n"
              << "Number of turns: " << turn_count(solution) << "\n"
              << c << std::endl;
}
