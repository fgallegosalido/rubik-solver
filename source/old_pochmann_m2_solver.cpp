#include <string>

#include "cube_algorithms.hpp"
#include "old_pochmann_m2_solver.hpp"
#include "utilities.hpp"

/*std::string OldPochmannM2Solver::apply_parity(){
    // If there's parity, we solve it
    if (corners_method.is_parity()){
        cube_ref << algorithms::parities::old_pochmann_m2;

        // We need to change both parities;
        corners_method.change_parity();
        edges_method.change_parity();
    }

    return algorithms::parities::full_old_pochmann + std::string{" "};
}*/

bool OldPochmannM2Solver::is_solved() const{
    return cube_ref.is_solved();
}

std::string OldPochmannM2Solver::solve(){
    std::string solution;

    solution += corners_method.solve();  // Apply corners method
    solution += " "/* + apply_parity()*/;    // Apply the parity
    solution += edges_method.solve();    // Apply edges method

    return cancel_moves(solution);
}
