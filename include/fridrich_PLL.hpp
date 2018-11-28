#ifndef _FRIDRICH_PLL_HPP_
#define _FRIDRICH_PLL_HPP_

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

#endif
