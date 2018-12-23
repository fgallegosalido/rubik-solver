#include <array>
#include <iostream>
#include <memory>

#include "cube.hpp"
#include "old_pochmann_solver.hpp"
#include "old_pochmann_blind_solver.hpp"
#include "old_pochmann_m2_solver.hpp"
#include "old_pochmann_m2_blind_solver.hpp"
#include "utilities.hpp"

int main(const int argc, const char *argv[]){
    std::string scramble;

    if (argc >= 2){
        for (int i=1; i<argc; ++i)
            scramble += argv[i] + std::string{" "};

        scramble = parse_algorithm(scramble);
    }
    else
        scramble = random_scramble();

    Cube c{scramble};

    std::cout << "Scramble: " << scramble << "\n"
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
                  << "Number of turns: " << turn_count(solution) << "\n";

        c << scramble;
    }
}
