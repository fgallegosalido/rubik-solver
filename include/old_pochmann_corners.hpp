#ifndef _OLD_POCHMANN_CORNERS_HPP_
#define _OLD_POCHMANN_CORNERS_HPP_

#include <memory>
#include <string>

#include "cube.hpp"
#include "method.hpp"

namespace algorithms::old_pochmann_corners{
    static constexpr const char* Ex = "R U' R' U' R U R' F' R U R' U' R' F R";

    static constexpr const char* UFL = "F R'";
    static constexpr const char* FLU = "F' D";
    static constexpr const char* LUF = "F2";
    static constexpr const char* URF = "F";
    static constexpr const char* RFU = "R'";
    static constexpr const char* FUR = "R2 D'";
    static constexpr const char* UBR = "R D'";
    static constexpr const char* BRU = "R' F";
    static constexpr const char* RUB = "R2";
    static constexpr const char* DLF = "F'";
    static constexpr const char* LFD = "F2 R'";
    static constexpr const char* FDL = "D";
    static constexpr const char* DFR = "F' R'";
    static constexpr const char* FRD = "R F";
    static constexpr const char* RDF = "";
    static constexpr const char* DRB = "R2 F";
    static constexpr const char* RBD = "R";
    static constexpr const char* BDR = "D'";
    static constexpr const char* DBL = "D F'";
    static constexpr const char* BLD = "D' R";
    static constexpr const char* LDB = "D2";
}

class OldPochmannCorners : public Method{
public:
    explicit OldPochmannCorners(Cube &ref)
        : Method{ref}{}

    void orientate_cube();
    void throw_piece(const char* commutator);
    bool method_finished();
    void apply_method() override;
};

#endif
