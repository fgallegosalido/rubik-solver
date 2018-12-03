#include <string>
#include "old_pochmann_blind_solver.hpp"
#include "utilities.hpp"

std::string OldPochmannBlindSolver::apply_parity(){
    std::string ret;

    // If there's parity, we solve it
    if (corners_method.is_parity()){
        ret += "U' ";
        ret += algorithms::PLL::R1;
        ret += " U ";

        // We need to change both parities;
        corners_method.change_parity();
        edges_method.change_parity();
    }

    cube_ref << ret;

    return ret;
}

std::string OldPochmannBlindSolver::solve(){
    std::string solution;

    solution += corners_method.apply_method();  // Apply corners method
    solution += " " + apply_parity();           // Apply the parity
    solution += edges_method.apply_method();    // Apply edges method

    return cancel_moves(solution);
}
