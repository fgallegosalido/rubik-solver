#ifndef _OLD_POCHMANN_CORNERS_HPP_
#define _OLD_POCHMANN_CORNERS_HPP_

#include <string>

#include "cube.hpp"
#include "cube_algorithms.hpp"
#include "method.hpp"

// Class that implements the old-pochmann method for corners
class OldPochmannCorners : public Method{
public:
    explicit OldPochmannCorners(Cube &ref)
        : Method{ref, "Old Pochmann Corners"}{}

    std::string orientate_cube();
    std::string throw_piece(const std::string &conjugation);

    bool method_finished() override;
    std::string apply_method() override;
};

#endif
