#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <string>
#include "cube.hpp"

// This abstract class describes the needed method for a solver
// The solver requires that the cube is solved once the
// solve() function is applied
class Solver {
protected:
    Cube &cube_ref;                 // A reference to the cube being solved
    const std::string &solver_name; // The solver name

public:
    explicit Solver(Cube &ref, const std::string &name_ = "Default solver name")
        : cube_ref{ref}, solver_name{name_}{}

    // A solver shouldn't be copied, so we delete those destructors
    Solver(const Solver&)            = delete;
    Solver(Solver&&)                 = delete;
    Solver& operator=(const Solver&) = delete;
    Solver& operator=(Solver&&)      = delete;

    virtual ~Solver()                = default;

    const std::string& name() const{
        return solver_name;
    }

    bool is_solved() const{
        return cube_ref.is_solved();
    }

    // Every solver must implement its own solve() function
    virtual std::string solve() = 0;
};

#endif
