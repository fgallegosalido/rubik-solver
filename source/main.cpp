#include <array>
#include <iostream>
#include <memory>

#include "cube.hpp"
#include "old_pochmann_solver.hpp"
#include "old_pochmann_blind_solver.hpp"
#include "old_pochmann_m2_solver.hpp"
#include "old_pochmann_m2_blind_solver.hpp"
#include "utilities.hpp"

int main(){
    auto scramble = random_scramble();
    Cube c{scramble};

    std::cout << "Random Scramble: " << scramble << "\n"
              << c << "\n";

    std::array<std::unique_ptr<Solver>, 4> solvers = {
        std::make_unique<OldPochmannSolver>(c),
        std::make_unique<OldPochmannBlindSolver>(c),
        std::make_unique<OldPochmannM2Solver>(c),
        std::make_unique<OldPochmannM2BlindSolver>(c)
    };

    for (const auto& solver : solvers){
        std::cout << "====================================================\n\n"
                  << "Solving the cube using " << solver->name() << "...\n" << std::endl;

        auto solution = solver->solve();

        std::cout << "Solution: "        << solution             << "\n"
                  << "Number of turns: " << turn_count(solution) << "\n"
                  << c << "\n";

        c << scramble;
    }
}
