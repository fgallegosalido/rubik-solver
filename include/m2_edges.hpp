#ifndef _M2_EDGES_HPP_
#define _M2_EDGES_HPP_

#include <string>

#include "cube.hpp"
#include "solver.hpp"

// Class that implements the old-pochmann method for corners
class M2Edges : public Solver{
private:
    bool parity = false;    // Keep track of the parity

public:
    explicit M2Edges(Cube &ref)
        : Solver{ref, "M2 for edges"}{}

    // Accessors for the parity
    void change_parity();
    const bool& is_parity() const;

    std::string throw_piece(const std::string &conjugation);

    bool is_solved() const override;
    std::string solve() override;
};

#endif
