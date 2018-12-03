#include <string>
#include "old_pochmann_solver.hpp"
#include "utilities.hpp"

std::string OldPochmannSolver::solve(){
    std::string solution;

    solution += corners_method.apply_method();  // Apply corners method
    solution += " ";                            // Separate methods
    solution += edges_method.apply_method();    // Apply edges method

    return cancel_moves(solution);
}
