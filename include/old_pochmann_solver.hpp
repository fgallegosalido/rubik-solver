#ifndef _OLD_POCHMANN_SOLVER_HPP_
#define _OLD_POCHMANN_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_corners.hpp"
#include "old_pochmann_edges.hpp"

// This class implements a solver using full old-pochmann
class OldPochmannSolver : public Solver{
protected:
    OldPochmannCorners corners_method;
    OldPochmannEdges edges_method;

    // This constructor is made private so derived
    // solvers can have their own names
    OldPochmannSolver(Cube &ref, const std::string &name)
        : Solver{ref, name},
          corners_method{ref},
          edges_method{ref}{}

public:
    explicit OldPochmannSolver(Cube &ref)
        : OldPochmannSolver{ref, "Full Old Pochmann"}{}

    std::string solve() override;
};

#endif
