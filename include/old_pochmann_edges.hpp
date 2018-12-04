#ifndef _OLD_POCHMANN_EDGES_HPP_
#define _OLD_POCHMANN_EDGES_HPP_

#include <string>

#include "cube.hpp"
#include "solver.hpp"

// Class that implements the old-pochmann method for edges
class OldPochmannEdges : public Solver{
private:
    bool parity = false;    // Keep track of parity

public:
    explicit OldPochmannEdges(Cube &ref)
        : Solver{ref, "Old Pochmann Edges"}{}

    // Accessors for the parity
    void change_parity();
    const bool& is_parity() const;

    std::string orientate_cube();
    std::string throw_piece(const std::string &conjugation);

    bool is_solved() const override;
    std::string solve() override;
};

#endif
