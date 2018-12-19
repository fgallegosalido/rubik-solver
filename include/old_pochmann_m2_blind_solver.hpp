#ifndef _OLD_POCHMANN_M2_BLIND_SOLVER_HPP_
#define _OLD_POCHMANN_M2_BLIND_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_m2_solver.hpp"

// This class implements a solver using old-pochmann for corners and M2
// for edges, but mindind about parities, so it could be used for blind
class OldPochmannM2BlindSolver : public OldPochmannM2Solver{
public:
    explicit OldPochmannM2BlindSolver(Cube &ref)
        : OldPochmannM2Solver{ref, "Old Pochmann + M2 Blind"}{}

    std::string apply_parity();
    std::string solve() override;
};

#endif
