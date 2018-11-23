#include "cube_storage.hpp"
#include "cube.hpp"

#include <sstream>
#include <algorithm>

namespace {
    constexpr const char* WHITE =   "\x1b[37m";
    constexpr const char* GREEN =   "\x1b[32m";
    constexpr const char* RED =     "\x1b[31m";
    constexpr const char* BLUE =    "\x1b[34m";
    constexpr const char* MAGENTA = "\x1b[35m";
    constexpr const char* YELLOW =  "\x1b[33m";
    constexpr const char* RESET =   "\x1b[0m";
    constexpr const char* SQUARE =  "\u25FC";
}

template<typename ...Args>
std::string Cube::colored_square(Args ...args){
    return (([](color c){
        switch(c){
            case white:
                return   WHITE + std::string{SQUARE} + RESET;
            case green:
                return   GREEN + std::string{SQUARE} + RESET;
            case red:
                return     RED + std::string{SQUARE} + RESET;
            case blue:
                return    BLUE + std::string{SQUARE} + RESET;
            case magenta:
                return MAGENTA + std::string{SQUARE} + RESET;
            case yellow:
                return  YELLOW + std::string{SQUARE} + RESET;
            default:
                return std::string{SQUARE};
        }
    }(args) + " ") + ... + '\b');
}

void Cube::turn_face(storage::size_type face, direction dir){
   switch (dir) {
      case clock_wise:
      {
         auto tmp = cube(face, 0);
         cube(face, 0) = cube(face, 6);
         cube(face, 6) = cube(face, 8);
         cube(face, 8) = cube(face, 2);
         cube(face, 2) = tmp;
         tmp = cube(face, 1);
         cube(face, 1) = cube(face, 3);
         cube(face, 3) = cube(face, 7);
         cube(face, 7) = cube(face, 5);
         cube(face, 5) = tmp; break;
      }
      case anti_clock_wise:
      {
         auto tmp = cube(face, 0);
         cube(face, 0) = cube(face, 2);
         cube(face, 2) = cube(face, 8);
         cube(face, 8) = cube(face, 6);
         cube(face, 6) = tmp;
         tmp = cube(face, 1);
         cube(face, 1) = cube(face, 5);
         cube(face, 5) = cube(face, 7);
         cube(face, 7) = cube(face, 3);
         cube(face, 3) = tmp; break;
      }
      case two_turns:
         std::swap(cube(face, 0), cube(face, 8));
         std::swap(cube(face, 1), cube(face, 7));
         std::swap(cube(face, 2), cube(face, 6));
         std::swap(cube(face, 3), cube(face, 5));
         break;
   }
}

// Canonical turns
void Cube::U(){
    // Exchange upper face squares
    turn_face(UP, clock_wise);

    auto tmp = cube(FRONT, 0);
    cube(FRONT, 0) = cube(RIGHT, 0);
    cube(RIGHT, 0) = cube(BACK, 0);
    cube(BACK, 0) = cube(LEFT, 0);
    cube(LEFT, 0) = tmp;

    tmp = cube(FRONT, 1);
    cube(FRONT, 1) = cube(RIGHT, 1);
    cube(RIGHT, 1) = cube(BACK, 1);
    cube(BACK, 1) = cube(LEFT, 1);
    cube(LEFT, 1) = tmp;

    tmp = cube(FRONT, 2);
    cube(FRONT, 2) = cube(RIGHT, 2);
    cube(RIGHT, 2) = cube(BACK, 2);
    cube(BACK, 2) = cube(LEFT, 2);
    cube(LEFT, 2) = tmp;
}
void Cube::Uu(){
    // Exchange upper face squares
    turn_face(UP, anti_clock_wise);

    auto tmp = cube(FRONT, 0);
    cube(FRONT, 0) = cube(LEFT, 0);
    cube(LEFT, 0) = cube(BACK, 0);
    cube(BACK, 0) = cube(RIGHT, 0);
    cube(RIGHT, 0) = tmp;

    tmp = cube(FRONT, 1);
    cube(FRONT, 1) = cube(LEFT, 1);
    cube(LEFT, 1) = cube(BACK, 1);
    cube(BACK, 1) = cube(RIGHT, 1);
    cube(RIGHT, 1) = tmp;

    tmp = cube(FRONT, 2);
    cube(FRONT, 2) = cube(LEFT, 2);
    cube(LEFT, 2) = cube(BACK, 2);
    cube(BACK, 2) = cube(RIGHT, 2);
    cube(RIGHT, 2) = tmp;
}
void Cube::U2(){
    // Exchange upper face squares
    turn_face(UP, two_turns);

    std::swap(cube(FRONT, 0), cube(BACK, 0));
    std::swap(cube(FRONT, 1), cube(BACK, 1));
    std::swap(cube(FRONT, 2), cube(BACK, 2));
    std::swap(cube(RIGHT, 0), cube(LEFT, 0));
    std::swap(cube(RIGHT, 1), cube(LEFT, 1));
    std::swap(cube(RIGHT, 2), cube(LEFT, 2));
}

void Cube::F(){
    // Exchange front face squares
    turn_face(FRONT, clock_wise);

    auto tmp = cube(UP, 6);
    cube(UP, 6) = cube(LEFT, 8);
    cube(LEFT, 8) = cube(DOWN, 2);
    cube(DOWN, 2) = cube(RIGHT, 0);
    cube(RIGHT, 0) = tmp;

    tmp = cube(UP, 7);
    cube(UP, 7) = cube(LEFT, 5);
    cube(LEFT, 5) = cube(DOWN, 1);
    cube(DOWN, 1) = cube(RIGHT, 3);
    cube(RIGHT, 3) = tmp;

    tmp = cube(UP, 8);
    cube(UP, 8) = cube(LEFT, 2);
    cube(LEFT, 2) = cube(DOWN, 0);
    cube(DOWN, 0) = cube(RIGHT, 6);
    cube(RIGHT, 6) = tmp;
}
void Cube::Ff(){
    // Exchange front face squares
    turn_face(FRONT, anti_clock_wise);

    auto tmp = cube(UP, 6);
    cube(UP, 6) = cube(RIGHT, 0);
    cube(RIGHT, 0) = cube(DOWN, 2);
    cube(DOWN, 2) = cube(LEFT, 8);
    cube(LEFT, 8) = tmp;

    tmp = cube(UP, 7);
    cube(UP, 7) = cube(RIGHT, 3);
    cube(RIGHT, 3) = cube(DOWN, 1);
    cube(DOWN, 1) = cube(LEFT, 5);
    cube(LEFT, 5) = tmp;

    tmp = cube(UP, 8);
    cube(UP, 8) = cube(RIGHT, 6);
    cube(RIGHT, 6) = cube(DOWN, 0);
    cube(DOWN, 0) = cube(LEFT, 2);
    cube(LEFT, 2) = tmp;
}
void Cube::F2(){
    // Exchange front face squares
    turn_face(FRONT, two_turns);

    std::swap(cube(UP, 6), cube(DOWN, 2));
    std::swap(cube(UP, 7), cube(DOWN, 1));
    std::swap(cube(UP, 8), cube(DOWN, 0));
    std::swap(cube(RIGHT, 0), cube(LEFT, 8));
    std::swap(cube(RIGHT, 3), cube(LEFT, 5));
    std::swap(cube(RIGHT, 6), cube(LEFT, 2));
}

void Cube::R(){
    // Exchange upper face squares
    turn_face(RIGHT, clock_wise);

    auto tmp = cube(UP, 2);
    cube(UP, 2) = cube(FRONT, 2);
    cube(FRONT, 2) = cube(DOWN, 2);
    cube(DOWN, 2) = cube(BACK, 6);
    cube(BACK, 6) = tmp;

    tmp = cube(UP, 5);
    cube(UP, 5) = cube(FRONT, 5);
    cube(FRONT, 5) = cube(DOWN, 5);
    cube(DOWN, 5) = cube(BACK, 3);
    cube(BACK, 3) = tmp;

    tmp = cube(UP, 8);
    cube(UP, 8) = cube(FRONT, 8);
    cube(FRONT, 8) = cube(DOWN, 8);
    cube(DOWN, 8) = cube(BACK, 0);
    cube(BACK, 0) = tmp;
}
void Cube::Rr(){
    // Exchange upper face squares
    turn_face(RIGHT, anti_clock_wise);

    auto tmp = cube(UP, 2);
    cube(UP, 2) = cube(BACK, 6);
    cube(BACK, 6) = cube(DOWN, 2);
    cube(DOWN, 2) = cube(FRONT, 2);
    cube(FRONT, 2) = tmp;

    tmp = cube(UP, 5);
    cube(UP, 5) = cube(BACK, 3);
    cube(BACK, 3) = cube(DOWN, 5);
    cube(DOWN, 5) = cube(FRONT, 5);
    cube(FRONT, 5) = tmp;

    tmp = cube(UP, 8);
    cube(UP, 8) = cube(BACK, 0);
    cube(BACK, 0) = cube(DOWN, 8);
    cube(DOWN, 8) = cube(FRONT, 8);
    cube(FRONT, 8) = tmp;
}
void Cube::R2(){
    // Exchange upper face squares
    turn_face(RIGHT, two_turns);

    std::swap(cube(UP, 2), cube(DOWN, 2));
    std::swap(cube(UP, 5), cube(DOWN, 5));
    std::swap(cube(UP, 8), cube(DOWN, 8));
    std::swap(cube(FRONT, 2), cube(BACK, 6));
    std::swap(cube(FRONT, 5), cube(BACK, 3));
    std::swap(cube(FRONT, 8), cube(BACK, 0));
}

void Cube::D(){
    // Exchange upper face squares
    turn_face(DOWN, clock_wise);

    auto tmp = cube(FRONT, 6);
    cube(FRONT, 6) = cube(LEFT, 6);
    cube(LEFT, 6) = cube(BACK, 6);
    cube(BACK, 6) = cube(RIGHT, 6);
    cube(RIGHT, 6) = tmp;

    tmp = cube(FRONT, 7);
    cube(FRONT, 7) = cube(LEFT, 7);
    cube(LEFT, 7) = cube(BACK, 7);
    cube(BACK, 7) = cube(RIGHT, 7);
    cube(RIGHT, 7) = tmp;

    tmp = cube(FRONT, 8);
    cube(FRONT, 8) = cube(LEFT, 8);
    cube(LEFT, 8) = cube(BACK, 8);
    cube(BACK, 8) = cube(RIGHT, 8);
    cube(RIGHT, 8) = tmp;
}
void Cube::Dd(){
    // Exchange upper face squares
    turn_face(DOWN, anti_clock_wise);

    auto tmp = cube(FRONT, 6);
    cube(FRONT, 6) = cube(RIGHT, 6);
    cube(RIGHT, 6) = cube(BACK, 6);
    cube(BACK, 6) = cube(LEFT, 6);
    cube(LEFT, 6) = tmp;

    tmp = cube(FRONT, 7);
    cube(FRONT, 7) = cube(RIGHT, 7);
    cube(RIGHT, 7) = cube(BACK, 7);
    cube(BACK, 7) = cube(LEFT, 7);
    cube(LEFT, 7) = tmp;

    tmp = cube(FRONT, 8);
    cube(FRONT, 8) = cube(RIGHT, 8);
    cube(RIGHT, 8) = cube(BACK, 8);
    cube(BACK, 8) = cube(LEFT, 8);
    cube(LEFT, 8) = tmp;
}
void Cube::D2(){
    // Exchange upper face squares
    turn_face(DOWN, two_turns);

    std::swap(cube(FRONT, 6), cube(BACK, 6));
    std::swap(cube(FRONT, 7), cube(BACK, 7));
    std::swap(cube(FRONT, 8), cube(BACK, 8));
    std::swap(cube(RIGHT, 6), cube(LEFT, 6));
    std::swap(cube(RIGHT, 7), cube(LEFT, 7));
    std::swap(cube(RIGHT, 8), cube(LEFT, 8));
}

void Cube::B(){
    // Exchange upper face squares
    turn_face(BACK, clock_wise);

    auto tmp = cube(UP, 0);
    cube(UP, 0) = cube(RIGHT, 2);
    cube(RIGHT, 2) = cube(DOWN, 8);
    cube(DOWN, 8) = cube(LEFT, 6);
    cube(LEFT, 6) = tmp;

    tmp = cube(UP, 1);
    cube(UP, 1) = cube(RIGHT, 5);
    cube(RIGHT, 5) = cube(DOWN, 7);
    cube(DOWN, 7) = cube(LEFT, 3);
    cube(LEFT, 3) = tmp;

    tmp = cube(UP, 2);
    cube(UP, 2) = cube(RIGHT, 8);
    cube(RIGHT, 8) = cube(DOWN, 6);
    cube(DOWN, 6) = cube(LEFT, 0);
    cube(LEFT, 0) = tmp;
}
void Cube::Bb(){
    // Exchange upper face squares
    turn_face(BACK, anti_clock_wise);

    auto tmp = cube(UP, 0);
    cube(UP, 0) = cube(LEFT, 6);
    cube(LEFT, 6) = cube(DOWN, 8);
    cube(DOWN, 8) = cube(RIGHT, 2);
    cube(RIGHT, 2) = tmp;

    tmp = cube(UP, 1);
    cube(UP, 1) = cube(LEFT, 3);
    cube(LEFT, 3) = cube(DOWN, 7);
    cube(DOWN, 7) = cube(RIGHT, 5);
    cube(RIGHT, 5) = tmp;

    tmp = cube(UP, 2);
    cube(UP, 2) = cube(LEFT, 0);
    cube(LEFT, 0) = cube(DOWN, 6);
    cube(DOWN, 6) = cube(RIGHT, 8);
    cube(RIGHT, 8) = tmp;
}
void Cube::B2(){
    // Exchange upper face squares
    turn_face(BACK, two_turns);

    std::swap(cube(UP, 0), cube(DOWN, 8));
    std::swap(cube(UP, 1), cube(DOWN, 7));
    std::swap(cube(UP, 2), cube(DOWN, 6));
    std::swap(cube(RIGHT, 2), cube(LEFT, 6));
    std::swap(cube(RIGHT, 5), cube(LEFT, 3));
    std::swap(cube(RIGHT, 8), cube(LEFT, 0));
}

void Cube::L(){
    // Exchange upper face squares
    turn_face(LEFT, clock_wise);

    auto tmp = cube(UP, 0);
    cube(UP, 0) = cube(BACK, 8);
    cube(BACK, 8) = cube(DOWN, 0);
    cube(DOWN, 0) = cube(FRONT, 0);
    cube(FRONT, 0) = tmp;

    tmp = cube(UP, 3);
    cube(UP, 3) = cube(BACK, 5);
    cube(BACK, 5) = cube(DOWN, 3);
    cube(DOWN, 3) = cube(FRONT, 3);
    cube(FRONT, 3) = tmp;

    tmp = cube(UP, 6);
    cube(UP, 6) = cube(BACK, 2);
    cube(BACK, 2) = cube(DOWN, 6);
    cube(DOWN, 6) = cube(FRONT, 6);
    cube(FRONT, 6) = tmp;
}
void Cube::Ll(){
    // Exchange upper face squares
    turn_face(LEFT, anti_clock_wise);

    auto tmp = cube(UP, 0);
    cube(UP, 0) = cube(FRONT, 0);
    cube(FRONT, 0) = cube(DOWN, 0);
    cube(DOWN, 0) = cube(BACK, 8);
    cube(BACK, 8) = tmp;

    tmp = cube(UP, 3);
    cube(UP, 3) = cube(FRONT, 3);
    cube(FRONT, 3) = cube(DOWN, 3);
    cube(DOWN, 3) = cube(BACK, 5);
    cube(BACK, 5) = tmp;

    tmp = cube(UP, 6);
    cube(UP, 6) = cube(FRONT, 6);
    cube(FRONT, 6) = cube(DOWN, 6);
    cube(DOWN, 6) = cube(BACK, 2);
    cube(BACK, 2) = tmp;
}
void Cube::L2(){
    // Exchange upper face squares
    turn_face(LEFT, two_turns);

    std::swap(cube(UP, 0), cube(DOWN, 0));
    std::swap(cube(UP, 3), cube(DOWN, 3));
    std::swap(cube(UP, 6), cube(DOWN, 6));
    std::swap(cube(FRONT, 0), cube(BACK, 8));
    std::swap(cube(FRONT, 3), cube(BACK, 5));
    std::swap(cube(FRONT, 6), cube(BACK, 2));
}

// Center layer turns
void Cube::M(){
    auto tmp = cube(UP, 1);
    cube(UP, 1) = cube(BACK, 7);
    cube(BACK, 7) = cube(DOWN, 1);
    cube(DOWN, 1) = cube(FRONT, 1);
    cube(FRONT, 1) = tmp;

    tmp = cube(UP, 4);
    cube(UP, 4) = cube(BACK, 4);
    cube(BACK, 4) = cube(DOWN, 4);
    cube(DOWN, 4) = cube(FRONT, 4);
    cube(FRONT, 4) = tmp;

    tmp = cube(UP, 7);
    cube(UP, 7) = cube(BACK, 1);
    cube(BACK, 1) = cube(DOWN, 7);
    cube(DOWN, 7) = cube(FRONT, 7);
    cube(FRONT, 7) = tmp;
}
void Cube::Mm(){
    auto tmp = cube(UP, 1);
    cube(UP, 1) = cube(FRONT, 1);
    cube(FRONT, 1) = cube(DOWN, 1);
    cube(DOWN, 1) = cube(BACK, 7);
    cube(BACK, 7) = tmp;

    tmp = cube(UP, 4);
    cube(UP, 4) = cube(FRONT, 4);
    cube(FRONT, 4) = cube(DOWN, 4);
    cube(DOWN, 4) = cube(BACK, 4);
    cube(BACK, 4) = tmp;

    tmp = cube(UP, 7);
    cube(UP, 7) = cube(FRONT, 7);
    cube(FRONT, 7) = cube(DOWN, 7);
    cube(DOWN, 7) = cube(BACK, 1);
    cube(BACK, 1) = tmp;
}
void Cube::M2(){
    std::swap(cube(UP, 1), cube(DOWN, 1));
    std::swap(cube(UP, 4), cube(DOWN, 4));
    std::swap(cube(UP, 7), cube(DOWN, 7));
    std::swap(cube(FRONT, 1), cube(BACK, 7));
    std::swap(cube(FRONT, 4), cube(BACK, 4));
    std::swap(cube(FRONT, 7), cube(BACK, 1));
}

void Cube::E(){
    auto tmp = cube(FRONT, 3);
    cube(FRONT, 3) = cube(LEFT, 3);
    cube(LEFT, 3) = cube(BACK, 3);
    cube(BACK, 3) = cube(RIGHT, 3);
    cube(RIGHT, 3) = tmp;

    tmp = cube(FRONT, 4);
    cube(FRONT, 4) = cube(LEFT, 4);
    cube(LEFT, 4) = cube(BACK, 4);
    cube(BACK, 4) = cube(RIGHT, 4);
    cube(RIGHT, 4) = tmp;

    tmp = cube(FRONT, 5);
    cube(FRONT, 5) = cube(LEFT, 5);
    cube(LEFT, 5) = cube(BACK, 5);
    cube(BACK, 5) = cube(RIGHT, 5);
    cube(RIGHT, 5) = tmp;
}
void Cube::Ee(){
    auto tmp = cube(FRONT, 3);
    cube(FRONT, 3) = cube(RIGHT, 3);
    cube(RIGHT, 3) = cube(BACK, 3);
    cube(BACK, 3) = cube(LEFT, 3);
    cube(LEFT, 3) = tmp;

    tmp = cube(FRONT, 4);
    cube(FRONT, 4) = cube(RIGHT, 4);
    cube(RIGHT, 4) = cube(BACK, 4);
    cube(BACK, 4) = cube(LEFT, 4);
    cube(LEFT, 4) = tmp;

    tmp = cube(FRONT, 5);
    cube(FRONT, 5) = cube(RIGHT, 5);
    cube(RIGHT, 5) = cube(BACK, 5);
    cube(BACK, 5) = cube(LEFT, 5);
    cube(LEFT, 5) = tmp;
}
void Cube::E2(){
    std::swap(cube(FRONT, 3), cube(BACK, 3));
    std::swap(cube(FRONT, 4), cube(BACK, 4));
    std::swap(cube(FRONT, 5), cube(BACK, 5));
    std::swap(cube(RIGHT, 3), cube(LEFT, 3));
    std::swap(cube(RIGHT, 4), cube(LEFT, 4));
    std::swap(cube(RIGHT, 5), cube(LEFT, 5));
}

void Cube::S(){
    auto tmp = cube(RIGHT, 1);
    cube(RIGHT, 1) = cube(UP, 3);
    cube(UP, 3) = cube(LEFT, 7);
    cube(LEFT, 7) = cube(DOWN, 5);
    cube(DOWN, 5) = tmp;

    tmp = cube(RIGHT, 4);
    cube(RIGHT, 4) = cube(UP, 4);
    cube(UP, 4) = cube(LEFT, 4);
    cube(LEFT, 4) = cube(DOWN, 4);
    cube(DOWN, 4) = tmp;

    tmp = cube(RIGHT, 7);
    cube(RIGHT, 7) = cube(UP, 5);
    cube(UP, 5) = cube(LEFT, 1);
    cube(LEFT, 1) = cube(DOWN, 3);
    cube(DOWN, 3) = tmp;
}
void Cube::Ss(){
    auto tmp = cube(RIGHT, 1);
    cube(RIGHT, 1) = cube(DOWN, 5);
    cube(DOWN, 5) = cube(LEFT, 7);
    cube(LEFT, 7) = cube(UP, 3);
    cube(UP, 3) = tmp;

    tmp = cube(RIGHT, 4);
    cube(RIGHT, 4) = cube(DOWN, 4);
    cube(DOWN, 4) = cube(LEFT, 4);
    cube(LEFT, 4) = cube(UP, 4);
    cube(UP, 4) = tmp;

    tmp = cube(RIGHT, 7);
    cube(RIGHT, 7) = cube(DOWN, 3);
    cube(DOWN, 3) = cube(LEFT, 1);
    cube(LEFT, 1) = cube(UP, 5);
    cube(UP, 5) = tmp;
}
void Cube::S2(){
    std::swap(cube(RIGHT, 1), cube(LEFT, 7));
    std::swap(cube(RIGHT, 4), cube(LEFT, 4));
    std::swap(cube(RIGHT, 7), cube(LEFT, 1));
    std::swap(cube(DOWN, 5), cube(UP, 3));
    std::swap(cube(DOWN, 4), cube(UP, 4));
    std::swap(cube(DOWN, 3), cube(UP, 5));
}

// Fat canonical turns
void Cube::u(){
    U(); Ee();
}
void Cube::uu(){
    Uu(); E();
}
void Cube::u2(){
    U2(); E2();
}

void Cube::f(){
    F(); S();
}
void Cube::ff(){
    Ff(); Ss();
}
void Cube::f2(){
    F2(); S2();
}

void Cube::r(){
    R(); Mm();
}
void Cube::rr(){
    Rr(); M();
}
void Cube::r2(){
    R2(); M2();
}

void Cube::d(){
    D(); E();
}
void Cube::dd(){
    Dd(); Ee();
}
void Cube::d2(){
    D2(); E2();
}

void Cube::b(){
    B(); Ss();
}
void Cube::bb(){
    Bb(); S();
}
void Cube::b2(){
    B2(); S2();
}

void Cube::l(){
    L(); M();
}
void Cube::ll(){
    Ll(); Mm();
}
void Cube::l2(){
    L2(); M2();
}

// Cube rotations
void Cube::x(){
    R(); Mm(); Ll();
}
void Cube::xx(){
    Rr(); M(); L();
}
void Cube::x2(){
    R2(); M2(); L2();
}

void Cube::y(){
    U(); Ee(); Dd();
}
void Cube::yy(){
    Uu(); E(); D();
}
void Cube::y2(){
    U2(); E2(); D2();
}

void Cube::z(){
    F(); S(); Bb();
}
void Cube::zz(){
    Ff(); Ss(); B();
}
void Cube::z2(){
    F2(); S2(); B2();
}

const color& Cube::UFL(){
    return cube(UP, 6);
}
const color& Cube::FLU(){
    return cube(FRONT, 0);
}
const color& Cube::LUF(){
    return cube(LEFT, 2)
}

const color& Cube::URF(){
    return cube(UP, 8);
}
const color& Cube::RFU(){
    return cube(RIGHT, 0);
}
const color& Cube::FUR(){
    return cube(FRONT, 2);
}

const color& Cube::UBR(){
    return cube(UP, 2);
}
const color& Cube::BRU(){
    return cube(BACK, 0);
}
const color& Cube::RUB(){
    return cube(RIGHT, 2);
}

const color& Cube::ULB(){
    return cube(UP, 0);
}
const color& Cube::LBU(){
    return cube(LEFT, 0);
}
const color& Cube::BUL(){
    return cube(BACK, 2);
}

const color& Cube::DLF(){
    return cube(DOWN, 0);
}
const color& Cube::LFD(){
    return cube(LEFT, 8);
}
const color& Cube::FDL(){
    return cube(FRONT, 6);
}

const color& Cube::DFR(){
    return cube(DOWN, 2);
}
const color& Cube::FRD(){
    return cube(FRONT, 8);
}
const color& Cube::RDF(){
    return cube(RIGHT, 6);
}

const color& Cube::DRB(){
    return cube(DOWN, 8);
}
const color& Cube::RBD(){
    return cube(RIGHT, 8);
}
const color& Cube::BDR(){
    return cube(BACK, 6);
}

const color& Cube::DBL(){
    return cube(DOWN, 6);
}
const color& Cube::BLD(){
    return cube(BACK, 8);
}
const color& Cube::LDB(){
    return cube(LEFT, 6);
}


// Edge stickers accessors
const color& Cube::UF(){
    return cube(UP, 7);
}
const color& Cube::FU(){
    return cube(FRONT, 1);
}

const color& Cube::UR(){
    return cube(UP, 5);
}
const color& Cube::RU(){
    return cube(RIGHT, 1);
}

const color& Cube::UB(){
    return cube(UP, 1);
}
const color& Cube::BU(){
    return cube(BACK, 1);
}

const color& Cube::UL(){
    return cube(UP, 3);
}
const color& Cube::LU(){
    return cube(LEFT, 1);
}

const color& Cube::FL(){
    return cube(FRONT, 3);
}
const color& Cube::LF(){
    return cube(LEFT, 5);
}

const color& Cube::FR(){
    return cube(FRONT, 5);
}
const color& Cube::RF(){
    return cube(RIGHT, 3);
}

const color& Cube::BR(){
    return cube(BACK, 3);
}
const color& Cube::RB(){
    return cube(RIGHT, 5);
}

const color& Cube::BL(){
    return cube(BACK, 5);
}
const color& Cube::LB(){
    return cube(LEFT, 3);
}

const color& Cube::DF(){
    return cube(DOWN, 1);
}
const color& Cube::FD(){
    return cube(FRONT, 7);
}

const color& Cube::DR(){
    return cube(DOWN, 5);
}
const color& Cube::RD(){
    return cube(RIGHT, 7);
}

const color& Cube::DB(){
    return cube(DOWN, 7);
}
const color& Cube::BD(){
    return cube(BACK, 7);
}

const color& Cube::DL(){
    return cube(DOWN, 3);
}
const color& Cube::LD(){
    return cube(LEFT, 7);
}

void Cube::read_algorithm(const std::string& alg){
    std::stringstream ss(alg);
    std::string turn;

    while (ss >> turn){
        if (turn.size() == 1){
            if      (turn[0] == 'U') U();
            else if (turn[0] == 'R') R();
            else if (turn[0] == 'F') F();
            else if (turn[0] == 'D') D();
            else if (turn[0] == 'B') B();
            else if (turn[0] == 'L') L();
            else if (turn[0] == 'M') M();
            else if (turn[0] == 'E') E();
            else if (turn[0] == 'S') S();
            else if (turn[0] == 'u') u();
            else if (turn[0] == 'r') r();
            else if (turn[0] == 'f') f();
            else if (turn[0] == 'd') d();
            else if (turn[0] == 'b') b();
            else if (turn[0] == 'l') l();
            else if (turn[0] == 'x') x();
            else if (turn[0] == 'y') y();
            else if (turn[0] == 'z') z();
        }
        else if (turn.size() == 2){
            if (turn[1] == '\''){
                if      (turn[0] == 'U') Uu();
                else if (turn[0] == 'R') Rr();
                else if (turn[0] == 'F') Ff();
                else if (turn[0] == 'D') Dd();
                else if (turn[0] == 'B') Bb();
                else if (turn[0] == 'L') Ll();
                else if (turn[0] == 'M') Mm();
                else if (turn[0] == 'E') Ee();
                else if (turn[0] == 'S') Ss();
                else if (turn[0] == 'u') uu();
                else if (turn[0] == 'r') rr();
                else if (turn[0] == 'f') ff();
                else if (turn[0] == 'd') dd();
                else if (turn[0] == 'b') bb();
                else if (turn[0] == 'l') ll();
                else if (turn[0] == 'x') xx();
                else if (turn[0] == 'y') yy();
                else if (turn[0] == 'z') zz();
            }
            else if (turn[1] == '2'){
                if      (turn[0] == 'U') U2();
                else if (turn[0] == 'R') R2();
                else if (turn[0] == 'F') F2();
                else if (turn[0] == 'D') D2();
                else if (turn[0] == 'B') B2();
                else if (turn[0] == 'L') L2();
                else if (turn[0] == 'M') M2();
                else if (turn[0] == 'E') E2();
                else if (turn[0] == 'S') S2();
                else if (turn[0] == 'u') u2();
                else if (turn[0] == 'r') r2();
                else if (turn[0] == 'f') f2();
                else if (turn[0] == 'd') d2();
                else if (turn[0] == 'b') b2();
                else if (turn[0] == 'l') l2();
                else if (turn[0] == 'x') x2();
                else if (turn[0] == 'y') y2();
                else if (turn[0] == 'z') z2();
            }
        }
    }
}

std::string Cube::inverse_algorithm(std::string alg){
    using namespace std::string_literals;
    std::reverse(alg.begin(), alg.end());
    std::stringstream ss(alg);
    std::string turn, ret;

    while (ss >> turn){
        if (turn.size() == 1)
            ret += turn + "' ";
        else if (turn.size() == 2){
            if (turn[0] == '\'')
                ret += turn.back() + " "s;
            else if (turn[0] == '2')
                ret += turn.back() + "2 "s;
        }
    }

    return ret;
}

/* WIP: Translate any algorithm to canonical moves (U, R, F, D, L, B)
void Cube::turn_to_canonical(std::string& t)
{
   auto aux = std::tolower(t[0]);

   if (aux == 'm' || aux == 'x' || aux == 'r' || aux == 'l'){
      for (auto i : parity){
         if (i.first == xy){

         }
         else if (i.first == xz){

         }
      }
   }
   else if (aux == 'e' || aux == 'y' || aux == 'u' || aux == 'd'){
      for (auto i : parity){
         if (i.first == xy){

         }
         else if (i.first == yz){

         }
      }
   }
   else if (aux == 's' || aux == 'z' || aux == 'f' || aux == 'b'){
      for (auto i : parity){
         if (i.first == yz){

         }
         else if (i.first == xz){

         }
      }
   }
   else{
      t = "";
   }
}

std::string Cube::algorithm_to_canonical(const std::string& alg){
   std::stringstream ss(alg);
   std::string ret;
   std::string turn;

   std::vector<std::pair<plane, direction>> parity;

   while (ss >> turn){
      if (turn == "M" || turn == "r'" || turn == "l" || turn == "x'"){
         parity.emplace_back(yz, clock_wise);
      }
      else if (turn == "M'" || turn == "r" || turn == "l'" || turn == "x"){
         parity.emplace_back(yz, anti_clock_wise);
      }
      else if (turn == "M2" || turn == "r2" || turn == "l2" || turn == "x2"){
         parity.emplace_back(yz, two_turns);
      }
      else if (turn == "E" || turn == "u'" || turn == "d" || turn == "y'"){
         parity.emplace_back(xz, clock_wise);
      }
      else if (turn == "E'" || turn == "u" || turn == "d'" || turn == "y"){
         parity.emplace_back(xz, anti_clock_wise);
      }
      else if (turn == "E2" || turn == "u2" || turn == "d2" || turn == "y2"){
         parity.emplace_back(xz, two_turns);
      }
      else if (turn == "S" || turn == "f" || turn == "b'" || turn == "z"){
         parity.emplace_back(xy, clock_wise);
      }
      else if (turn == "S'" || turn == "f'" || turn == "b" || turn == "z'"){
         parity.emplace_back(xy, anti_clock_wise);
      }
      else if (turn == "S2" || turn == "f2" || turn == "b2" || turn == "z2"){
         parity.emplace_back(xy, two_turns);
      }

      ret += turn_to_canonical(turn, parity);
   }

   return ret;
}
*/

bool Cube::is_solved() const{
   return std::all_of(cube.begin(), cube.end()-1, [](const auto& f){
       return std::all_of(f.begin()+1, f.end(), [&first = *f.begin()](const auto& c){
           return first == c;
       });
   });
}

std::ostream& operator<<(std::ostream& out, Cube& c){
   out   << "      " << c.colored_square(c.cube(c.UP, 0), c.cube(c.UP, 1), c.cube(c.UP, 2)) << "\n"
         << "      " << c.colored_square(c.cube(c.UP, 3), c.cube(c.UP, 4), c.cube(c.UP, 5)) << "\n"
         << "      " << c.colored_square(c.cube(c.UP, 6), c.cube(c.UP, 7), c.cube(c.UP, 8)) << "\n"
         << c.colored_square(c.cube(c.LEFT, 0), c.cube(c.LEFT, 1), c.cube(c.LEFT, 2), c.cube(c.FRONT, 0), c.cube(c.FRONT, 1), c.cube(c.FRONT, 2), c.cube(c.RIGHT, 0), c.cube(c.RIGHT, 1), c.cube(c.RIGHT, 2), c.cube(c.BACK, 0), c.cube(c.BACK, 1), c.cube(c.BACK, 2)) << "\n"
         << c.colored_square(c.cube(c.LEFT, 3), c.cube(c.LEFT, 4), c.cube(c.LEFT, 5), c.cube(c.FRONT, 3), c.cube(c.FRONT, 4), c.cube(c.FRONT, 5), c.cube(c.RIGHT, 3), c.cube(c.RIGHT, 4), c.cube(c.RIGHT, 5), c.cube(c.BACK, 3), c.cube(c.BACK, 4), c.cube(c.BACK, 5)) << "\n"
         << c.colored_square(c.cube(c.LEFT, 6), c.cube(c.LEFT, 7), c.cube(c.LEFT, 8), c.cube(c.FRONT, 6), c.cube(c.FRONT, 7), c.cube(c.FRONT, 8), c.cube(c.RIGHT, 6), c.cube(c.RIGHT, 7), c.cube(c.RIGHT, 8), c.cube(c.BACK, 6), c.cube(c.BACK, 7), c.cube(c.BACK, 8)) << "\n"
         << "      " << c.colored_square(c.cube(c.DOWN, 0), c.cube(c.DOWN, 1), c.cube(c.DOWN, 2)) << "\n"
         << "      " << c.colored_square(c.cube(c.DOWN, 3), c.cube(c.DOWN, 4), c.cube(c.DOWN, 5)) << "\n"
         << "      " << c.colored_square(c.cube(c.DOWN, 6), c.cube(c.DOWN, 7), c.cube(c.DOWN, 8));

   return out;
}
