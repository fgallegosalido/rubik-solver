#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <ostream>
#include <sstream>
#include <string>
#include <string_view>

#include "color.hpp"
#include "cube_storage.hpp"

class Cube : public CubeStorage {
public:
    constexpr Cube()                             = default;
    constexpr Cube(const Cube& other)            = default;
    constexpr Cube(Cube&& other)                 = default;
    constexpr Cube& operator=(const Cube& other) = default;
    constexpr Cube& operator=(Cube&& other)      = default;
    ~Cube()                                      = default;

    // Initialize the cube with a random scramble of the given length
    explicit Cube(std::size_t length);

    // A cube can be initialized with a scramble (passed as a string type)
    template <typename CharT, typename Traits, typename Allocator>
    explicit Cube(const std::basic_string<CharT, Traits, Allocator> &scramble)
        : Cube{} { read_algorithm(scramble); }

    template <typename CharT, typename Traits>
    explicit constexpr Cube(const std::basic_string_view<CharT, Traits> &scramble) noexcept
        : Cube{} { read_algorithm(scramble); }

    template <typename CharT>
    explicit constexpr Cube(const CharT *scramble)
        : Cube{std::basic_string_view<CharT>{scramble}} {}

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
    [[nodiscard]] constexpr const_reference UFL() const{ return get(UP   , 6); }
    [[nodiscard]] constexpr const_reference FLU() const{ return get(FRONT, 0); }
    [[nodiscard]] constexpr const_reference LUF() const{ return get(LEFT , 2); }

    [[nodiscard]] constexpr const_reference URF() const{ return get(UP   , 8); }
    [[nodiscard]] constexpr const_reference RFU() const{ return get(RIGHT, 0); }
    [[nodiscard]] constexpr const_reference FUR() const{ return get(FRONT, 2); }

    [[nodiscard]] constexpr const_reference UBR() const{ return get(UP   , 2); }
    [[nodiscard]] constexpr const_reference BRU() const{ return get(BACK , 0); }
    [[nodiscard]] constexpr const_reference RUB() const{ return get(RIGHT, 2); }

    [[nodiscard]] constexpr const_reference ULB() const{ return get(UP   , 0); }
    [[nodiscard]] constexpr const_reference LBU() const{ return get(LEFT , 0); }
    [[nodiscard]] constexpr const_reference BUL() const{ return get(BACK , 2); }

    [[nodiscard]] constexpr const_reference DLF() const{ return get(DOWN , 0); }
    [[nodiscard]] constexpr const_reference LFD() const{ return get(LEFT , 8); }
    [[nodiscard]] constexpr const_reference FDL() const{ return get(FRONT, 6); }

    [[nodiscard]] constexpr const_reference DFR() const{ return get(DOWN , 2); }
    [[nodiscard]] constexpr const_reference FRD() const{ return get(FRONT, 8); }
    [[nodiscard]] constexpr const_reference RDF() const{ return get(RIGHT, 6); }

    [[nodiscard]] constexpr const_reference DRB() const{ return get(DOWN , 8); }
    [[nodiscard]] constexpr const_reference RBD() const{ return get(RIGHT, 8); }
    [[nodiscard]] constexpr const_reference BDR() const{ return get(BACK , 6); }

    [[nodiscard]] constexpr const_reference DBL() const{ return get(DOWN , 6); }
    [[nodiscard]] constexpr const_reference BLD() const{ return get(BACK , 8); }
    [[nodiscard]] constexpr const_reference LDB() const{ return get(LEFT , 6); }

    // Edge stickers accessors
    [[nodiscard]] constexpr const_reference UF() const{ return get(UP   , 7); }
    [[nodiscard]] constexpr const_reference FU() const{ return get(FRONT, 1); }

    [[nodiscard]] constexpr const_reference UR() const{ return get(UP   , 5); }
    [[nodiscard]] constexpr const_reference RU() const{ return get(RIGHT, 1); }

    [[nodiscard]] constexpr const_reference UB() const{ return get(UP   , 1); }
    [[nodiscard]] constexpr const_reference BU() const{ return get(BACK , 1); }

    [[nodiscard]] constexpr const_reference UL() const{ return get(UP   , 3); }
    [[nodiscard]] constexpr const_reference LU() const{ return get(LEFT , 1); }

    [[nodiscard]] constexpr const_reference FL() const{ return get(FRONT, 3); }
    [[nodiscard]] constexpr const_reference LF() const{ return get(LEFT , 5); }

    [[nodiscard]] constexpr const_reference FR() const{ return get(FRONT, 5); }
    [[nodiscard]] constexpr const_reference RF() const{ return get(RIGHT, 3); }

    [[nodiscard]] constexpr const_reference BR() const{ return get(BACK , 3); }
    [[nodiscard]] constexpr const_reference RB() const{ return get(RIGHT, 5); }

    [[nodiscard]] constexpr const_reference BL() const{ return get(BACK , 5); }
    [[nodiscard]] constexpr const_reference LB() const{ return get(LEFT , 3); }

    [[nodiscard]] constexpr const_reference DF() const{ return get(DOWN , 1); }
    [[nodiscard]] constexpr const_reference FD() const{ return get(FRONT, 7); }

    [[nodiscard]] constexpr const_reference DR() const{ return get(DOWN , 5); }
    [[nodiscard]] constexpr const_reference RD() const{ return get(RIGHT, 7); }

    [[nodiscard]] constexpr const_reference DB() const{ return get(DOWN , 7); }
    [[nodiscard]] constexpr const_reference BD() const{ return get(BACK , 7); }

    [[nodiscard]] constexpr const_reference DL() const{ return get(DOWN , 3); }
    [[nodiscard]] constexpr const_reference LD() const{ return get(LEFT , 7); }

    // Center stickers accessors
    [[nodiscard]] constexpr const_reference Uc() const{ return get(UP   , 4); }
    [[nodiscard]] constexpr const_reference Fc() const{ return get(FRONT, 4); }
    [[nodiscard]] constexpr const_reference Rc() const{ return get(RIGHT, 4); }
    [[nodiscard]] constexpr const_reference Bc() const{ return get(BACK , 4); }
    [[nodiscard]] constexpr const_reference Lc() const{ return get(LEFT , 4); }
    [[nodiscard]] constexpr const_reference Dc() const{ return get(DOWN , 4); }


    // Check if the cube is solved
    [[nodiscard]] bool is_solved() const;

    // Reads an algorithm as a string

    template <typename CharT, typename Traits, typename Allocator>
    void read_algorithm(const std::basic_string<CharT, Traits, Allocator> &alg){
        // We assume each move is space-separated, otherwise it will not be
        // done. That's why sstream is so convenient
        // Maybe a more complex parser will be implemented (to allow move
        // repetitions)
        std::basic_stringstream<CharT> ss{alg};
        std::basic_string<CharT, Traits, Allocator> turn;

        while (ss >> turn){
            if (turn.size() == 1){  // The turn is clock-wise
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
                if (turn[1] == '\''){   // If the turn is anti-clock-wise
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
                else if (turn[1] == '2'){   // If the turn is 180º
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

    template <typename CharT, typename Traits>
    void read_algorithm(const std::basic_string_view<CharT, Traits> &alg){
        read_algorithm(std::basic_string<CharT>{alg.data()});
    }

    template <typename CharT>
    void read_algorithm(const CharT *alg){
        read_algorithm(std::basic_string<CharT>{alg});
    }

    // Handy operator to make moves in the cube
    template <typename CharT, typename Traits, typename Allocator>
    Cube& operator<<(const std::basic_string<CharT, Traits, Allocator> &alg){
        read_algorithm(alg);
        return *this;
    }

    template <typename CharT, typename Traits>
    Cube& operator<<(const std::basic_string_view<CharT, Traits> &alg){
        read_algorithm(std::basic_string<CharT, Traits>{alg.data()});
        return *this;
    }

    template <typename CharT>
    Cube& operator<<(const CharT *alg){
        read_algorithm(std::basic_string<CharT>{alg});
        return *this;
    }

    // Reads a sticker position as a string (Not implemented yet)
    //const_reference read_position(const std::string& pos) const;

    // Prints the cube in the console in a fancy way
    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<< (std::basic_ostream<CharT, Traits> &out, const Cube &c){
        out << '\n';

        for (face_size_type i=0; i<3; ++i){
            out << "      ";
            for (face_size_type j=0; j<3; ++j)
                out << c.m_colors[c(UP, i*3 + j)] << "\u25FC\x1b[0m ";
            out << '\n';
        }

        for (face_size_type i=0; i<3; ++i){
            for (face_size_type j=0; j<3; ++j)
                out << c.m_colors[c(LEFT, i*3 + j)] << "\u25FC\x1b[0m ";

            for (face_size_type j=FRONT; j<=BACK; ++j)
                for (face_size_type k=0; k<3; ++k)
                    out << c.m_colors[c(j, i*3 + k)] << "\u25FC\x1b[0m ";
            out << '\n';
        }

        for (face_size_type i=0; i<3; ++i){
            out << "      ";
            for (face_size_type j=0; j<3; ++j)
                out << c.m_colors[c(DOWN, i*3 + j)] << "\u25FC\x1b[0m ";
            out << '\n';
        }

       return out;
    }

private:
    // Default colors of the cube
    std::array<Color, 6> m_colors{
        Color{255, 255, 255},   // White  (Up)
        Color{0  , 255, 0  },   // Green  (Front)
        Color{255, 0  , 0  },   // Red    (Right)
        Color{0  , 0  , 255},   // Blue   (Back)
        Color{255, 95 , 0  },   // Orange (Left)
        Color{255, 255, 0  }    // Yellow (Down)
    };
    // Some helper functions
    // This enumerate is used to decide wich direction a face is turned
    enum direction {clock_wise, anti_clock_wise, two_turns};
    void turn_face(cube_size_type face, direction dir);
};

#endif
