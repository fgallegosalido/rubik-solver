#ifndef _CROSS_HPP_
#define _CROSS_HPP_

#include <deque>
#include <string>
#include <utility>

#include "cube.hpp"
#include "solver.hpp"
#include "orientator.hpp"

// Solver that builds the white cross
class Cross : Solver{
private:
    void solve_impl(std::deque<std::string> &solution, unsigned depth);

public:
    explicit Cross(Cube &ref)
        : Solver{ref, "Cross"}{}

    bool is_solved() const override;
    std::string solve() override;
};

#endif
