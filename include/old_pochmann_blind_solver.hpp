#ifndef _OLD_POCHMANN_BLIND_SOLVER_HPP_
#define _OLD_POCHMANN_BLIND_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_corners.hpp"
#include "old_pochmann_edges.hpp"

// This class implements a solver using full old-pochmann
class OldPochmannBlindSolver : public Solver{
private:
    OldPochmannCorners corners_method;
    OldPochmannEdges edges_method;
    
public:
    explicit OldPochmannBlindSolver(Cube &ref)
        : Solver{ref, "Full Old Pochmann Blind"},
          corners_method{ref},
          edges_method{ref}{}

    std::string apply_parity();
    std::string solve() override;
};

#endif
