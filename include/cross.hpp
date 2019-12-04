#ifndef _CROSS_HPP_
#define _CROSS_HPP_

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "cube.hpp"
#include "solver.hpp"
#include "orientator.hpp"

// Solver that builds the white cross
class Cross : Solver{
private:
    bool solve_impl(unsigned depth, std::vector<std::string_view> &v, const Cube &original);

public:
    explicit Cross(Cube &ref)
        : Solver{ref, "Cross"}{}

    bool is_solved() const override;
    std::string solve() override;
};

#endif
