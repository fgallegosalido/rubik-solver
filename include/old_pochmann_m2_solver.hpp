#ifndef _OLD_POCHMANN_M2_SOLVER_HPP_
#define _OLD_POCHMANN_M2_SOLVER_HPP_

#include <string>
#include "cube.hpp"
#include "solver.hpp"
#include "old_pochmann_corners.hpp"
#include "m2_edges.hpp"

// This class implements a solver using old-pochmann for corners
// and M2 for edges.
class OldPochmannM2Solver : public Solver{
private:
    OldPochmannCorners corners_method;
    M2Edges edges_method;
public:
    explicit OldPochmannM2Solver(Cube &ref)
        : Solver{ref, "Old Pochmann + M2"},
          corners_method{ref},
          edges_method{ref}{}

    std::string apply_parity();
    
    bool is_solved() const override;
    std::string solve() override;
};

#endif
