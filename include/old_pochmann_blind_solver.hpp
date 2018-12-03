#ifndef _OLD_POCHMANN_BLIND_SOLVER_HPP_
#define _OLD_POCHMANN_BLIND_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_solver.hpp"

// This class implements a solver using full old-pochmann
class OldPochmannBlindSolver : public OldPochmannSolver{
public:
    explicit OldPochmannBlindSolver(Cube &ref)
        : OldPochmannSolver{ref, "Full Old Pochmann Blind"}{}

    std::string apply_parity();
    std::string solve() override;
};

#endif
