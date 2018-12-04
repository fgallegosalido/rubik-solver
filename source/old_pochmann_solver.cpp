#include <string>
#include "old_pochmann_solver.hpp"
#include "utilities.hpp"

bool OldPochmannSolver::is_solved() const{
    return cube_ref.is_solved();
}

std::string OldPochmannSolver::solve(){
    std::string solution;

    solution += corners_method.solve();  // Apply corners method
    solution += " ";                            // Separate methods
    solution += edges_method.solve();    // Apply edges method

    return cancel_moves(solution);
}
