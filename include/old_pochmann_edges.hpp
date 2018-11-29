#ifndef _OLD_POCHMANN_EDGES_HPP_
#define _OLD_POCHMANN_EDGES_HPP_

#include <memory>
#include <string>

#include "cube.hpp"
#include "cube_algorithms.hpp"
#include "method.hpp"

class OldPochmannEdges : public Method{
public:
    explicit OldPochmannEdges(Cube &ref)
        : Method{ref, "Old Pochmann Edges"}{}

    void orientate_cube();
    void throw_piece(const char* conjugation);
    bool method_finished();
    [[nodiscard]] std::string apply_method() override;
};

#endif
