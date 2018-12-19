#include <string>

#include "cube_algorithms.hpp"
#include "old_pochmann_m2_solver.hpp"
#include "utilities.hpp"

bool OldPochmannM2Solver::is_solved() const{
    return cube_ref.is_solved();
}

std::string OldPochmannM2Solver::solve(){
    std::string solution;

    solution += corners_method.solve();  // Apply corners method
    solution += " ";                     // Separate methods
    solution += edges_method.solve();    // Apply edges method

    return cancel_moves(solution);
}
