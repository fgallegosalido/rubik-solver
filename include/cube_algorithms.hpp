#ifndef _CUBE_ALGORITHMS_HPP_
#define _CUBE_ALGORITHMS_HPP_

// Algorithms for the method PLL
namespace algorithms::PLL{
   static constexpr const char* A1 = "x R' U R' D2 R U' R' D2 R2 x'";
   static constexpr const char* A2 = "x R2 D2 R U R' D2 R U' R x'";
   static constexpr const char* E = "x' R U' R' D R U R' D' R U R' D R U' R' D' x";
   static constexpr const char* U1 = "R U' R U R U R U' R' U' R2";
   static constexpr const char* U2 = "R2 U R U R' U' R' U' R' U R'";
   static constexpr const char* H = "M2 U M2 U2 M2 U M2";
   static constexpr const char* Z = "M2 U M2 U M' U2 M2 U2 M' U2";
   static constexpr const char* T = "R U R' U' R' F R2 U' R' U' R U R' F'";
   static constexpr const char* F = "R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R";
   static constexpr const char* J1 = "L' U' L F L' U' L U L F' L2 U L U";
   static constexpr const char* J2 = "R U R' F' R U R' U' R' F R2 U' R' U'";
   static constexpr const char* R1 = "L U2 L' U2 L F' L' U' L U L F L2 U";
   static constexpr const char* R2 = "R' U2 R U2 R' F R U R' U' R' F' R2 U'";
   static constexpr const char* Y = "F R U' R' U' R U R' F' R U R' U' R' F R F'";
   static constexpr const char* V = "R' U R' d' R' F' R2 U' R' U R' F R F y'";
   static constexpr const char* N1 = "L U' R U2 L' U L R' U' R U2 L' U R' U'";
   static constexpr const char* N2 = "R' U L' U2 R U' R' L U L' U2 R U' L U";
   static constexpr const char* G1 = "R2 u R' U R' U' R u' R2 y' R' U' R";
   static constexpr const char* G2 = "F' U' F R2 u R' U R U' R u' R2";
   static constexpr const char* G3 = "R2 u' R U' R U R' u R2 y R U' R'";
   static constexpr const char* G4 = "R U R' y' R2 u' R U' R' U R' u R2";
}

// Algorithms for the old-pochmann method for corners
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

// Algorithms for the old-pochmann method for edges
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

#endif
