#ifndef _ORIENTATOR_HPP_
#define _ORIENTATOR_HPP_

#include <string>
#include <utility>
#include "solver.hpp"

// This template class is just a solver that orientates the cube
// in a certain position
//
// Keep in mind that, if you choose two non-adjecent colors, the
// solver, basically, won't work
template <color Up, color Front>
class Orientator : public Solver {
public:
    explicit Orientator(Cube &ref)
        : Solver{ref, "Orientator"}{}

    // Every solver must implement its own is_solved() and solve() function
    bool is_solved() const override{
        return cube_ref.Uc()==Up && cube_ref.Fc()==Front;
    }

    // Just orientates the cube in a certain position
    std::string solve() override{
        std::pair<std::string, std::string> orientation;

        if (cube_ref.Fc() == Up)
            orientation.first += "x ";
        else if (cube_ref.Rc() == Up)
            orientation.first += "z' ";
        else if (cube_ref.Bc() == Up)
            orientation.first += "x' ";
        else if (cube_ref.Lc() == Up)
            orientation.first += "z ";
        else if (cube_ref.Dc() == Up)
            orientation.first += "x2 ";

        cube_ref << orientation.first;

        if (cube_ref.Rc() == Front)
            orientation.second += "y";
        else if (cube_ref.Bc() == Front)
            orientation.second += "y2";
        else if (cube_ref.Lc() == Front)
            orientation.second += "y'";

        cube_ref << orientation.second;
        return orientation.first + orientation.second;
    }
};

#endif
