#ifndef _OLD_POCHMANN_CORNERS_HPP_
#define _OLD_POCHMANN_CORNERS_HPP_

#include <string>

#include "cube.hpp"
#include "solver.hpp"

// Class that implements the old-pochmann method for corners
class OldPochmannCorners : public Solver{
private:
    bool parity = false;    // Keep track of the parity

public:
    explicit OldPochmannCorners(Cube &ref)
        : Solver{ref, "Old Pochmann Corners"}{}

    // Accessors for the parity
    void change_parity();
    const bool& is_parity() const;

    std::string throw_piece(const std::string &conjugation);

    bool is_solved() const override;
    std::string solve() override;
};

#endif
