#include "cube_storage.hpp"
#include "cube.hpp"

#include <algorithm>
#include <sstream>

namespace {
    // In this unnamed namespace we define all I need to print the cube.

    // These are the variables that store the output color
    constexpr const char* WHITE =   "\x1b[37m";
    constexpr const char* GREEN =   "\x1b[32m";
    constexpr const char* RED =     "\x1b[31m";
    constexpr const char* BLUE =    "\x1b[34m";
    constexpr const char* MAGENTA = "\x1b[35m";
    constexpr const char* YELLOW =  "\x1b[33m";
    constexpr const char* RESET =   "\x1b[0m";
    constexpr const char* SQUARE =  "\u25FC";

    // Function that prints a variable amount of colored squares
    template<typename ...Args>
    std::string colored_square(Args ...args){
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
}

Cube::Cube(const std::string& scramble){
    read_algorithm(scramble);
}

// This function turns the 9 squares of a face in a certain direction
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
// These turns must be hard-coded
// It looks like so much repetition, but it's not,
// so that's what have to be done
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
// These ones also have to be hard-coded
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

// The rest of the turns can be implemented based on the previous ones
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

// Accessors by the sticker namespace
// Corner stickers accessors
const color& Cube::UFL() const{
    return cube(UP, 6);
}
const color& Cube::FLU() const{
    return cube(FRONT, 0);
}
const color& Cube::LUF() const{
    return cube(LEFT, 2);
}

const color& Cube::URF() const{
    return cube(UP, 8);
}
const color& Cube::RFU() const{
    return cube(RIGHT, 0);
}
const color& Cube::FUR() const{
    return cube(FRONT, 2);
}

const color& Cube::UBR() const{
    return cube(UP, 2);
}
const color& Cube::BRU() const{
    return cube(BACK, 0);
}
const color& Cube::RUB() const{
    return cube(RIGHT, 2);
}

const color& Cube::ULB() const{
    return cube(UP, 0);
}
const color& Cube::LBU() const{
    return cube(LEFT, 0);
}
const color& Cube::BUL() const{
    return cube(BACK, 2);
}

const color& Cube::DLF() const{
    return cube(DOWN, 0);
}
const color& Cube::LFD() const{
    return cube(LEFT, 8);
}
const color& Cube::FDL() const{
    return cube(FRONT, 6);
}

const color& Cube::DFR() const{
    return cube(DOWN, 2);
}
const color& Cube::FRD() const{
    return cube(FRONT, 8);
}
const color& Cube::RDF() const{
    return cube(RIGHT, 6);
}

const color& Cube::DRB() const{
    return cube(DOWN, 8);
}
const color& Cube::RBD() const{
    return cube(RIGHT, 8);
}
const color& Cube::BDR() const{
    return cube(BACK, 6);
}

const color& Cube::DBL() const{
    return cube(DOWN, 6);
}
const color& Cube::BLD() const{
    return cube(BACK, 8);
}
const color& Cube::LDB() const{
    return cube(LEFT, 6);
}

// Edge stickers accessors
const color& Cube::UF() const{
    return cube(UP, 7);
}
const color& Cube::FU() const{
    return cube(FRONT, 1);
}

const color& Cube::UR() const{
    return cube(UP, 5);
}
const color& Cube::RU() const{
    return cube(RIGHT, 1);
}

const color& Cube::UB() const{
    return cube(UP, 1);
}
const color& Cube::BU() const{
    return cube(BACK, 1);
}

const color& Cube::UL() const{
    return cube(UP, 3);
}
const color& Cube::LU() const{
    return cube(LEFT, 1);
}

const color& Cube::FL() const{
    return cube(FRONT, 3);
}
const color& Cube::LF() const{
    return cube(LEFT, 5);
}

const color& Cube::FR() const{
    return cube(FRONT, 5);
}
const color& Cube::RF() const{
    return cube(RIGHT, 3);
}

const color& Cube::BR() const{
    return cube(BACK, 3);
}
const color& Cube::RB() const{
    return cube(RIGHT, 5);
}

const color& Cube::BL() const{
    return cube(BACK, 5);
}
const color& Cube::LB() const{
    return cube(LEFT, 3);
}

const color& Cube::DF() const{
    return cube(DOWN, 1);
}
const color& Cube::FD() const{
    return cube(FRONT, 7);
}

const color& Cube::DR() const{
    return cube(DOWN, 5);
}
const color& Cube::RD() const{
    return cube(RIGHT, 7);
}

const color& Cube::DB() const{
    return cube(DOWN, 7);
}
const color& Cube::BD() const{
    return cube(BACK, 7);
}

const color& Cube::DL() const{
    return cube(DOWN, 3);
}
const color& Cube::LD() const{
    return cube(LEFT, 7);
}


// Center stickers accessors
const color& Cube::Uc() const{
    return cube(UP, 4);
}
const color& Cube::Fc() const{
    return cube(FRONT, 4);
}
const color& Cube::Rc() const{
    return cube(RIGHT, 4);
}
const color& Cube::Bc() const{
    return cube(BACK, 4);
}
const color& Cube::Lc() const{
    return cube(LEFT, 4);
}
const color& Cube::Dc() const{
    return cube(DOWN, 4);
}

// Helper function that reads a single turn
void Cube::read_turn(const std::string& t){
    if (t.size() == 1){  // The turn is clock-wise
        if      (t[0] == 'U') U();
        else if (t[0] == 'R') R();
        else if (t[0] == 'F') F();
        else if (t[0] == 'D') D();
        else if (t[0] == 'B') B();
        else if (t[0] == 'L') L();
        else if (t[0] == 'M') M();
        else if (t[0] == 'E') E();
        else if (t[0] == 'S') S();
        else if (t[0] == 'u') u();
        else if (t[0] == 'r') r();
        else if (t[0] == 'f') f();
        else if (t[0] == 'd') d();
        else if (t[0] == 'b') b();
        else if (t[0] == 'l') l();
        else if (t[0] == 'x') x();
        else if (t[0] == 'y') y();
        else if (t[0] == 'z') z();
    }
    else if (t.size() == 2){
        if (t[1] == '\''){   // If the turn is anti-clock-wise
            if      (t[0] == 'U') Uu();
            else if (t[0] == 'R') Rr();
            else if (t[0] == 'F') Ff();
            else if (t[0] == 'D') Dd();
            else if (t[0] == 'B') Bb();
            else if (t[0] == 'L') Ll();
            else if (t[0] == 'M') Mm();
            else if (t[0] == 'E') Ee();
            else if (t[0] == 'S') Ss();
            else if (t[0] == 'u') uu();
            else if (t[0] == 'r') rr();
            else if (t[0] == 'f') ff();
            else if (t[0] == 'd') dd();
            else if (t[0] == 'b') bb();
            else if (t[0] == 'l') ll();
            else if (t[0] == 'x') xx();
            else if (t[0] == 'y') yy();
            else if (t[0] == 'z') zz();
        }
        else if (t[1] == '2'){   // If the turn is 180º
            if      (t[0] == 'U') U2();
            else if (t[0] == 'R') R2();
            else if (t[0] == 'F') F2();
            else if (t[0] == 'D') D2();
            else if (t[0] == 'B') B2();
            else if (t[0] == 'L') L2();
            else if (t[0] == 'M') M2();
            else if (t[0] == 'E') E2();
            else if (t[0] == 'S') S2();
            else if (t[0] == 'u') u2();
            else if (t[0] == 'r') r2();
            else if (t[0] == 'f') f2();
            else if (t[0] == 'd') d2();
            else if (t[0] == 'b') b2();
            else if (t[0] == 'l') l2();
            else if (t[0] == 'x') x2();
            else if (t[0] == 'y') y2();
            else if (t[0] == 'z') z2();
        }
    }
}


void Cube::read_algorithm(const std::string &alg){
    // We assume each move is space-separated, otherwise it will not be
    // done. That's why sstream is so convenient
    // Maybe a more complex parser will be implemented (to allow move
    // repetitions)
    std::stringstream ss(alg);
    std::string turn;

    while (ss >> turn){
        read_turn(turn);
    }
}

Cube& Cube::operator<<(const std::string &alg){
    read_algorithm(alg);
    return *this;
}

bool Cube::is_solved() const{
   return std::all_of(cube.begin(), cube.end()-1, [](const auto& f){
       return std::all_of(f.begin()+1, f.end(), [&first = *f.begin()](const auto& c){
           return first == c;
       });
   });
}

std::ostream& operator<<(std::ostream& out, Cube& c){
   out   << "      " << colored_square(c(Cube::UP, 0), c(Cube::UP, 1), c(Cube::UP, 2)) << "\n"
         << "      " << colored_square(c(Cube::UP, 3), c(Cube::UP, 4), c(Cube::UP, 5)) << "\n"
         << "      " << colored_square(c(Cube::UP, 6), c(Cube::UP, 7), c(Cube::UP, 8)) << "\n"
         << colored_square(c(Cube::LEFT, 0), c(Cube::LEFT, 1), c(Cube::LEFT, 2), c(Cube::FRONT, 0), c(Cube::FRONT, 1), c(Cube::FRONT, 2), c(Cube::RIGHT, 0), c(Cube::RIGHT, 1), c(Cube::RIGHT, 2), c(Cube::BACK, 0), c(Cube::BACK, 1), c(Cube::BACK, 2)) << "\n"
         << colored_square(c(Cube::LEFT, 3), c(Cube::LEFT, 4), c(Cube::LEFT, 5), c(Cube::FRONT, 3), c(Cube::FRONT, 4), c(Cube::FRONT, 5), c(Cube::RIGHT, 3), c(Cube::RIGHT, 4), c(Cube::RIGHT, 5), c(Cube::BACK, 3), c(Cube::BACK, 4), c(Cube::BACK, 5)) << "\n"
         << colored_square(c(Cube::LEFT, 6), c(Cube::LEFT, 7), c(Cube::LEFT, 8), c(Cube::FRONT, 6), c(Cube::FRONT, 7), c(Cube::FRONT, 8), c(Cube::RIGHT, 6), c(Cube::RIGHT, 7), c(Cube::RIGHT, 8), c(Cube::BACK, 6), c(Cube::BACK, 7), c(Cube::BACK, 8)) << "\n"
         << "      " << colored_square(c(Cube::DOWN, 0), c(Cube::DOWN, 1), c(Cube::DOWN, 2)) << "\n"
         << "      " << colored_square(c(Cube::DOWN, 3), c(Cube::DOWN, 4), c(Cube::DOWN, 5)) << "\n"
         << "      " << colored_square(c(Cube::DOWN, 6), c(Cube::DOWN, 7), c(Cube::DOWN, 8));

   return out;
}
