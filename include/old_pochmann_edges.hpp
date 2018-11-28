#ifndef _OLD_POCHMANN_EDGES_HPP_
#define _OLD_POCHMANN_EDGES_HPP_

#include <memory>
#include <string>

#include "cube.hpp"
#include "method.hpp"

namespace algorithms::old_pochmann_edges{
    static constexpr const char* Ex = "R U R' U' R' F R2 U' R' U' R U R' F'";

    static constexpr const char* UF = "R2 U R2";
    static constexpr const char* FU = "R F' L' F R'";
    static constexpr const char* UB = "R2 U' R2";
    static constexpr const char* BU = "R' B L B' R";
    static constexpr const char* UL = "";
    static constexpr const char* LU = "L U' F U";
    static constexpr const char* FL = "L'";
    static constexpr const char* LF = "U' F U";
    static constexpr const char* FR = "U2 R U2";
    static constexpr const char* RF = "U' F' U";
    static constexpr const char* BR = "U2 R' U2";
    static constexpr const char* RB = "U B U'";
    static constexpr const char* BL = "L";
    static constexpr const char* LB = "U B' U'";
    static constexpr const char* DF = "D' L2";
    static constexpr const char* FD = "F L' F'";
    static constexpr const char* DR = "D2 L2";
    static constexpr const char* RD = "D' F L' F'";
    static constexpr const char* DB = "D L2";
    static constexpr const char* BD = "B' L B";
    static constexpr const char* DL = "L2";
    static constexpr const char* LD = "D F L' F'";
}

class OldPochmannEdges : public Method{
public:
    explicit OldPochmannEdges(Cube &ref)
        : Method{ref}{}

    void orientate_cube();
    void throw_piece(const char* commutator);
    bool method_finished();
    void apply_method() override;
};

#endif
