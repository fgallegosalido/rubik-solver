#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <string>
#include "cube.hpp"

// This abstract class describes the needed method for a solver
// The solver requires that the cube is solved once the
// solve() function is applied
class Solver {
protected:
    Cube &cube_ref;
    const std::string &solver_name;

public:
    explicit Solver(Cube &ref, const std::string &name = "Default solver name")
        : cube_ref{ref}, solver_name{name}{}

    bool is_solved() const{
        return cube_ref.is_solved();
    }

    virtual std::string solve() = 0;
};

#endif
