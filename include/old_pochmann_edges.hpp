#ifndef _OLD_POCHMANN_EDGES_HPP_
#define _OLD_POCHMANN_EDGES_HPP_

#include <string>

#include "cube.hpp"
#include "cube_algorithms.hpp"
#include "method.hpp"

// Class that implements the old-pochmann method for edges
class OldPochmannEdges : public Method{
public:
    explicit OldPochmannEdges(Cube &ref)
        : Method{ref, "Old Pochmann Edges"}{}

    std::string orientate_cube();
    std::string throw_piece(const std::string &conjugation);

    bool method_finished() override;
    std::string apply_method() override;
};

#endif
