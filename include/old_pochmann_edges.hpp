#ifndef _OLD_POCHMANN_EDGES_HPP_
#define _OLD_POCHMANN_EDGES_HPP_

#include <string>

#include "cube.hpp"
#include "cube_algorithms.hpp"
#include "method.hpp"

// Class that implements the old-pochmann method for edges
class OldPochmannEdges : public Method{
private:
    bool parity = false;

public:
    explicit OldPochmannEdges(Cube &ref)
        : Method{ref, "Old Pochmann Edges"}{}

    void change_parity();
    const bool& is_parity() const;

    std::string orientate_cube();
    std::string throw_piece(const std::string &conjugation);

    bool method_finished() const override;
    std::string apply_method() override;
};

#endif
