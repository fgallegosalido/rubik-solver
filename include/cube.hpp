#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cube_storage.hpp"

enum color {white, green, red, blue, magenta, yellow};

class Cube{
private:
    using storage = CubeStorage<color>;

    // This enumerate is used to decide wich direction a face is turned
    enum direction {clock_wise, anti_clock_wise, two_turns};
public:
    Cube()                             = default;
    Cube(const Cube& other)            = default;
    Cube(Cube&& other)                 = default;
    Cube& operator=(const Cube& other) = default;
    Cube& operator=(Cube&& other)      = default;
    ~Cube()                            = default;

    // A cube can be initialized with a scramble
    explicit Cube(const std::string& scramble);

    // As in the storage, we can access a face by its name
    static constexpr auto UP    = storage::UP;
    static constexpr auto FRONT = storage::FRONT;
    static constexpr auto RIGHT = storage::RIGHT;
    static constexpr auto BACK  = storage::BACK;
    static constexpr auto LEFT  = storage::LEFT;
    static constexpr auto DOWN  = storage::DOWN;

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


    // Center stickers accessors
    const color& Uc() const;
    const color& Fc() const;
    const color& Rc() const;
    const color& Bc() const;
    const color& Lc() const;
    const color& Dc() const;


    // Check if the cube is solved
    bool is_solved() const;
    // Reads an algorithm as a string
    void read_algorithm(const std::string& alg);
    // Reads a sticker position as a string
    const color& read_position(const std::string& pos) const;

    using value_type             = typename storage::value_type;
    using size_type              = typename storage::size_type;
    using reference              = typename storage::reference;
    using const_reference        = typename storage::const_reference;
    using iterator               = typename storage::iterator;
    using const_iterator         = typename storage::const_iterator;
    using reverse_iterator       = typename storage::reverse_iterator;
    using const_reverse_iterator = typename storage::const_reverse_iterator;

    // Access a specific sticker by its face and position
    constexpr typename value_type::reference operator()(size_type face, size_type pos) noexcept {
        return cube(face, pos);
    }
    constexpr typename value_type::const_reference operator()(size_type face, size_type pos) const noexcept {
        return cube(face, pos);
    }


    // Iterator functions that lets you iterate through each face
    constexpr iterator begin() noexcept{
        return cube.begin();
    }
    constexpr const_iterator begin() const noexcept{
        return cube.begin();
    }

    constexpr iterator end() noexcept{
        return cube.end();
    }
    constexpr const_iterator end() const noexcept{
        return cube.end();
    }

    constexpr reverse_iterator rbegin() noexcept{
        return cube.rbegin();
    }
    constexpr const_reverse_iterator rbegin() const noexcept{
        return cube.rbegin();
    }

    constexpr reverse_iterator rend() noexcept{
        return cube.rend();
    }
    constexpr const_reverse_iterator rend() const noexcept{
        return cube.rend();
    }

    constexpr const_iterator cbegin() noexcept{
        return cube.cbegin();
    }
    constexpr const_iterator cend() noexcept{
        return cube.cend();
    }

    constexpr const_reverse_iterator crbegin() noexcept{
        return cube.crbegin();
    }
    constexpr const_reverse_iterator crend() noexcept{
        return cube.crend();
    }

    // Prints the cube in the console in a fancy way
    friend std::ostream& operator<<(std::ostream &out, Cube &c);

private:
    // The cube variable. It's always initialized as a solved cube
    storage cube{{{ // <-- This is bulls***. Please help
        {white, white, white, white, white, white, white, white, white},
        {green, green, green, green, green, green, green, green, green},
        {red, red, red, red, red, red, red, red, red},
        {blue, blue, blue, blue, blue, blue, blue, blue, blue},
        {magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta},
        {yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow}
    }}};

    // Some helper functions
    void turn_face(storage::size_type face, direction dir);
    void read_turn(const std::string &t);
};

#endif
