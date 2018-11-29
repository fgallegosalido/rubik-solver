#ifndef _OLD_POCHMANN_CORNERS_HPP_
#define _OLD_POCHMANN_CORNERS_HPP_

#include <string>

#include "cube.hpp"
#include "cube_algorithms.hpp"
#include "method.hpp"

class OldPochmannCorners : public Method{
public:
    explicit OldPochmannCorners(Cube &ref)
        : Method{ref, "Old Pochmann Corners"}{}

    void orientate_cube();
    void throw_piece(const char* conjugation);
    bool method_finished();
    [[nodiscard]] std::string apply_method() override;
};

#endif
