#include <array>
#include <iostream>

#include "cube.hpp"
#include "old_pochmann_solver.hpp"
#include "old_pochmann_blind_solver.hpp"
#include "old_pochmann_m2_solver.hpp"
#include "utilities.hpp"

int main(){
    auto scramble = random_scramble();
    Cube c{scramble};

    std::cout << "Random Scramble: " << scramble << "\n"
              << c << "\n" << std::endl;

    std::array<Solver*, 3> solvers = {
        new OldPochmannSolver{c},
        new OldPochmannBlindSolver{c},
        new OldPochmannM2Solver{c}
    };

    for (const auto& solver : solvers){
        std::cout << "\n====================================================\n\n"
                  << "Solving the cube using " << solver->name() << "\n" << std::endl;

        auto solution = solver->solve();

        std::cout << "Solution: "        << solution             << "\n"
                  << "Number of turns: " << turn_count(solution) << "\n\n"
                  << c << std::endl;

        c << scramble;
    }
}
