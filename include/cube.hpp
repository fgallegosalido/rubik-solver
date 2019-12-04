#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <algorithm>
#include <cstdint>
#include <optional>
#include <ostream>
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
        : Cube{} { read_algorithm(scramble); }

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

    template <typename CharT, typename Traits>
    [[nodiscard]] constexpr std::optional<value_type>
    operator[](const std::basic_string_view<CharT, Traits> &pos) const{
        if (pos == "UFL" || pos == "ULF") return UFL();
        if (pos == "FLU" || pos == "FUL") return FLU();
        if (pos == "LUF" || pos == "LFU") return LUF();
        if (pos == "URF" || pos == "UFR") return URF();
        if (pos == "RFU" || pos == "RUF") return RFU();
        if (pos == "FUR" || pos == "FRU") return FUR();
        if (pos == "UBR" || pos == "URB") return UBR();
        if (pos == "BRU" || pos == "BUR") return BRU();
        if (pos == "RUB" || pos == "RBU") return RUB();
        if (pos == "ULB" || pos == "UBL") return ULB();
        if (pos == "LBU" || pos == "LUB") return LBU();
        if (pos == "BUL" || pos == "BLU") return BUL();
        if (pos == "DLF" || pos == "DFL") return DLF();
        if (pos == "LFD" || pos == "LDF") return LFD();
        if (pos == "FDL" || pos == "FLD") return FDL();
        if (pos == "DFR" || pos == "DRF") return DFR();
        if (pos == "FRD" || pos == "FDR") return FRD();
        if (pos == "RDF" || pos == "RFD") return RDF();
        if (pos == "DRB" || pos == "DBR") return DRB();
        if (pos == "RBD" || pos == "RDB") return RBD();
        if (pos == "BDR" || pos == "BRD") return BDR();
        if (pos == "DBL" || pos == "DLB") return DBL();
        if (pos == "BLD" || pos == "BDL") return BLD();
        if (pos == "LDB" || pos == "LBD") return LDB();

        if (pos == "UF") return UF();
        if (pos == "FU") return FU();
        if (pos == "UR") return UR();
        if (pos == "RU") return RU();
        if (pos == "UB") return UB();
        if (pos == "BU") return BU();
        if (pos == "UL") return UL();
        if (pos == "LU") return LU();
        if (pos == "FL") return FL();
        if (pos == "LF") return LF();
        if (pos == "FR") return FR();
        if (pos == "RF") return RF();
        if (pos == "BR") return BR();
        if (pos == "RB") return RB();
        if (pos == "BL") return BL();
        if (pos == "LB") return LB();
        if (pos == "DF") return DF();
        if (pos == "FD") return FD();
        if (pos == "DR") return DR();
        if (pos == "RD") return RD();
        if (pos == "DB") return DB();
        if (pos == "BD") return BD();
        if (pos == "DL") return DL();
        if (pos == "LD") return LD();

        if (pos == "U") return Uc();
        if (pos == "F") return Fc();
        if (pos == "R") return Rc();
        if (pos == "B") return Bc();
        if (pos == "L") return Lc();
        if (pos == "D") return Dc();

        return std::nullopt;
    }

    template <typename CharT, typename Traits, typename Allocator>
    [[nodiscard]] constexpr std::optional<value_type>
    operator[](const std::basic_string<CharT, Traits, Allocator> &pos) const{
        return this->operator[](std::basic_string_view<CharT, Traits>{pos});
    }

    template <typename CharT>
    [[nodiscard]] constexpr std::optional<value_type>
    operator[](const CharT *pos) const{
        return this->operator[](std::basic_string_view<CharT>{pos});
    }

    // Check if the cube is solved
    [[nodiscard]] bool is_solved() const;

    // Reads an algorithm as a string
    template <typename CharT, typename Traits>
    constexpr void read_algorithm(const std::basic_string_view<CharT, Traits> &alg){
        for (auto first = alg.find_first_not_of(' '); first < alg.size();){
            auto last = std::min(alg.size(), alg.find_first_of(' ', first));

            if (last-first == 1){  // The turn is clock-wise
                if      (alg[first] == 'U') U();
                else if (alg[first] == 'R') R();
                else if (alg[first] == 'F') F();
                else if (alg[first] == 'D') D();
                else if (alg[first] == 'B') B();
                else if (alg[first] == 'L') L();
                else if (alg[first] == 'M') M();
                else if (alg[first] == 'E') E();
                else if (alg[first] == 'S') S();
                else if (alg[first] == 'u') u();
                else if (alg[first] == 'r') r();
                else if (alg[first] == 'f') f();
                else if (alg[first] == 'd') d();
                else if (alg[first] == 'b') b();
                else if (alg[first] == 'l') l();
                else if (alg[first] == 'x') x();
                else if (alg[first] == 'y') y();
                else if (alg[first] == 'z') z();
            }
            else if (last-first == 2){
                if (alg[first+1] == '\''){   // If the turn is anti-clock-wise
                    if      (alg[first] == 'U') Uu();
                    else if (alg[first] == 'R') Rr();
                    else if (alg[first] == 'F') Ff();
                    else if (alg[first] == 'D') Dd();
                    else if (alg[first] == 'B') Bb();
                    else if (alg[first] == 'L') Ll();
                    else if (alg[first] == 'M') Mm();
                    else if (alg[first] == 'E') Ee();
                    else if (alg[first] == 'S') Ss();
                    else if (alg[first] == 'u') uu();
                    else if (alg[first] == 'r') rr();
                    else if (alg[first] == 'f') ff();
                    else if (alg[first] == 'd') dd();
                    else if (alg[first] == 'b') bb();
                    else if (alg[first] == 'l') ll();
                    else if (alg[first] == 'x') xx();
                    else if (alg[first] == 'y') yy();
                    else if (alg[first] == 'z') zz();
                }
                else if (alg[first+1] == '2'){   // If the turn is 180º
                    if      (alg[first] == 'U') U2();
                    else if (alg[first] == 'R') R2();
                    else if (alg[first] == 'F') F2();
                    else if (alg[first] == 'D') D2();
                    else if (alg[first] == 'B') B2();
                    else if (alg[first] == 'L') L2();
                    else if (alg[first] == 'M') M2();
                    else if (alg[first] == 'E') E2();
                    else if (alg[first] == 'S') S2();
                    else if (alg[first] == 'u') u2();
                    else if (alg[first] == 'r') r2();
                    else if (alg[first] == 'f') f2();
                    else if (alg[first] == 'd') d2();
                    else if (alg[first] == 'b') b2();
                    else if (alg[first] == 'l') l2();
                    else if (alg[first] == 'x') x2();
                    else if (alg[first] == 'y') y2();
                    else if (alg[first] == 'z') z2();
                }
            }

            first = alg.find_first_not_of(' ', last);
        }
    }

    template <typename CharT, typename Traits, typename Allocator>
    void read_algorithm(const std::basic_string<CharT, Traits, Allocator> &alg){
        read_algorithm(std::basic_string_view<CharT, Traits>{alg});
    }

    template <typename CharT>
    constexpr void read_algorithm(const CharT *alg){
        read_algorithm(std::basic_string_view<CharT>{alg});
    }

    // Handy operator to make moves in the cube
    template <typename CharT, typename Traits, typename Allocator>
    Cube& operator<<(const std::basic_string<CharT, Traits, Allocator> &alg){
        read_algorithm(alg);
        return *this;
    }

    template <typename CharT, typename Traits>
    constexpr Cube& operator<<(const std::basic_string_view<CharT, Traits> &alg){
        read_algorithm(alg);
        return *this;
    }

    template <typename CharT>
    constexpr Cube& operator<<(const CharT *alg){
        read_algorithm(alg);
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
