#ifndef _OLD_POCHMANN_SOLVER_HPP_
#define _OLD_POCHMANN_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_corners.hpp"
#include "old_pochmann_edges.hpp"

// This class implements a solver using full old-pochmann
class OldPochmannSolver : public Solver{
private:
    // Here we define the two methods used to solve the cube
    OldPochmannCorners corners_method;
    OldPochmannEdges edges_method;

public:
    explicit OldPochmannSolver(Cube &ref)
        : Solver{ref, "Full Old Pochmann"}, corners_method{ref}, edges_method{ref}{}

    std::string solve() override;
};

#endif
