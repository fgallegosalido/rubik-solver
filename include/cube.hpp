#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cube_storage.hpp"

enum color {white, green, red, blue, magenta, yellow};
enum direction {clock_wise, anti_clock_wise, two_turns};
enum plane {xy, yz, xz};

class Cube{
public:
    Cube() = default;

    // Canonical turns
    void U();
    void Uu();
    void U2();

    void F();
    void Ff();
    void F2();

    void R();
    void Rr();
    void R2();

    void D();
    void Dd();
    void D2();

    void B();
    void Bb();
    void B2();

    void L();
    void Ll();
    void L2();


    // Center layer turns
    void M();
    void Mm();
    void M2();

    void E();
    void Ee();
    void E2();

    void S();
    void Ss();
    void S2();

    // Fat canonical turns
    void u();
    void uu();
    void u2();

    void f();
    void ff();
    void f2();

    void r();
    void rr();
    void r2();

    void d();
    void dd();
    void d2();

    void b();
    void bb();
    void b2();

    void l();
    void ll();
    void l2();


    // Cube rotations
    void x();
    void xx();
    void x2();

    void y();
    void yy();
    void y2();

    void z();
    void zz();
    void z2();


    // Corner stickers accessors
    const color& UFL() const;
    const color& FLU() const;
    const color& LUF() const;

    const color& URF() const;
    const color& RFU() const;
    const color& FUR() const;

    const color& UBR() const;
    const color& BRU() const;
    const color& RUB() const;

    const color& ULB() const;
    const color& LBU() const;
    const color& BUL() const;

    const color& DLF() const;
    const color& LFD() const;
    const color& FDL() const;

    const color& DFR() const;
    const color& FRD() const;
    const color& RDF() const;

    const color& DRB() const;
    const color& RBD() const;
    const color& BDR() const;

    const color& DBL() const;
    const color& BLD() const;
    const color& LDB() const;


    // Edge stickers accessors
    const color& UF() const;
    const color& FU() const;

    const color& UR() const;
    const color& RU() const;

    const color& UB() const;
    const color& BU() const;

    const color& UL() const;
    const color& LU() const;

    const color& FL() const;
    const color& LF() const;

    const color& FR() const;
    const color& RF() const;

    const color& BR() const;
    const color& RB() const;

    const color& BL() const;
    const color& LB() const;

    const color& DF() const;
    const color& FD() const;

    const color& DR() const;
    const color& RD() const;

    const color& DB() const;
    const color& BD() const;

    const color& DL() const;
    const color& LD() const;


    // Other functions
    bool is_solved() const;
    std::string inverse_algorithm(std::string alg);
    void read_algorithm(const std::string& alg);
    //std::string algorithm_to_canonical(const std::string& alg);

    friend std::ostream& operator<<(std::ostream& out, Cube& c);

private:
    using storage = cube_storage<color>;

    storage cube{{{ // <-- This is bulls***. Please help
        {white, white, white, white, white, white, white, white, white},
        {green, green, green, green, green, green, green, green, green},
        {red, red, red, red, red, red, red, red, red},
        {blue, blue, blue, blue, blue, blue, blue, blue, blue},
        {magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta},
        {yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow}
    }}};

    static constexpr auto UP    = storage::UP;
    static constexpr auto FRONT = storage::FRONT;
    static constexpr auto RIGHT = storage::RIGHT;
    static constexpr auto BACK  = storage::BACK;
    static constexpr auto LEFT  = storage::LEFT;
    static constexpr auto DOWN  = storage::DOWN;

    template<typename ...Args>
    std::string colored_square(Args ...args);

    void turn_face(storage::size_type face, direction dir);
    void read_turn(const std::string& t);
    //void turn_to_canonical(std::string& t, const std::vector<std::pair<plane, direction>>& parity);
};

#endif
