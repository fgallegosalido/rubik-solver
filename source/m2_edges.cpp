#include <algorithm>

#include "cube_algorithms.hpp"
#include "m2_edges.hpp"
#include "utilities.hpp"

#pragma GCC diagnostic ignored "-Wswitch"

void M2Edges::change_parity(){
    parity = !parity;
}

const bool& M2Edges::is_parity() const{
    return parity;
}

// To apply the method, the cube must be up-white and front-green
std::string M2Edges::orientate_cube(){
    std::string orientation;

    if (cube_ref.Fc() == white)
        orientation += "x ";
    else if (cube_ref.Rc() == white)
        orientation += "z' ";
    else if (cube_ref.Bc() == white)
        orientation += "x' ";
    else if (cube_ref.Lc() == white)
        orientation += "z ";
    else if (cube_ref.Dc() == white)
        orientation += "x2 ";

    if (cube_ref.Rc() == green)
        orientation += "y ";
    else if (cube_ref.Bc() == green)
        orientation += "y2 ";
    else if (cube_ref.Lc() == green)
        orientation += "y' ";

    cube_ref << orientation;
    return orientation;
}

// This function throws the buffer piece to a specific position
std::string M2Edges::throw_piece(const std::string &conjugation){
    if (conjugation==algorithms::m2_edges::UF ||
        conjugation==algorithms::m2_edges::FU ||
        conjugation==algorithms::m2_edges::DB ||
        conjugation==algorithms::m2_edges::BD)
    {
        cube_ref << conjugation;
        change_parity();

        return conjugation + " ";
    }
    else{
        cube_ref << conjugation
                 << algorithms::m2_edges::Ex
                 << inverse_algorithm(conjugation);

        change_parity();

        return conjugation                    + " "
             + algorithms::m2_edges::Ex       + " "
             + inverse_algorithm(conjugation) + " ";
    }
}

// Just check if the corners are solved
bool M2Edges::is_solved() const{
    if (parity){
        Cube aux{cube_ref};
        aux << "M2 F2 U"
            << algorithms::PLL::T
            << "U' F2";

        return std::all_of(aux.begin(), aux.end()-1, [](const auto& face){
            return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
        });
    }
    else{
        return std::all_of(cube_ref.begin(), cube_ref.end()-1, [](const auto& face){
            return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
        });
    }
}

std::string M2Edges::solve(){
    // Variable that will hold the final solution
    auto solution = orientate_cube();

    while (!is_solved()){
        // First we check that the piece in the buffer is not in its position
        if ((cube_ref.FD()!=green || cube_ref.DF()!=yellow) && (cube_ref.FD()!=yellow || cube_ref.DF()!=green)){
            // Checks the buffer piece and throws it to its correct position
            switch (cube_ref.DF()){
                case white:
                    switch (cube_ref.FD()) {
                        case green:{
                            if (parity)
                                solution += throw_piece(algorithms::m2_edges::DB);
                            else
                                solution += throw_piece(algorithms::m2_edges::UF);
                            } break;
                        case red:
                            solution += throw_piece(algorithms::m2_edges::UR); break;
                        case blue:
                            solution += throw_piece(algorithms::m2_edges::UB); break;
                        case magenta:
                            solution += throw_piece(algorithms::m2_edges::UL); break;
                    } break;
                case green:
                    switch (cube_ref.FD()){
                        case white:{
                            if (parity)
                                solution += throw_piece(algorithms::m2_edges::BD);
                            else
                                solution += throw_piece(algorithms::m2_edges::FU);
                            } break;
                        case magenta:
                            solution += throw_piece(algorithms::m2_edges::FL); break;
                        case red:
                            solution += throw_piece(algorithms::m2_edges::FR); break;
                    } break;
                case red:
                    switch (cube_ref.FD()){
                        case white:
                            solution += throw_piece(algorithms::m2_edges::RU); break;
                        case green:
                            solution += throw_piece(algorithms::m2_edges::RF); break;
                        case yellow:
                            solution += throw_piece(algorithms::m2_edges::RD); break;
                        case blue:
                            solution += throw_piece(algorithms::m2_edges::RB); break;
                    } break;
                case blue:
                    switch (cube_ref.FD()){
                        case white:
                            solution += throw_piece(algorithms::m2_edges::BU); break;
                        case red:
                            solution += throw_piece(algorithms::m2_edges::BR); break;
                        case yellow:{
                            if (parity)
                                solution += throw_piece(algorithms::m2_edges::FU);
                            else
                                solution += throw_piece(algorithms::m2_edges::BD);
                            } break;
                        case magenta:
                            solution += throw_piece(algorithms::m2_edges::BL); break;
                    } break;
                case magenta:
                    switch (cube_ref.FD()){
                        case white:
                            solution += throw_piece(algorithms::m2_edges::LU); break;
                        case blue:
                            solution += throw_piece(algorithms::m2_edges::LB); break;
                        case yellow:
                            solution += throw_piece(algorithms::m2_edges::LD); break;
                        case green:
                            solution += throw_piece(algorithms::m2_edges::LF); break;
                    } break;
                case yellow:
                    switch (cube_ref.FD()){
                        case red:
                            solution += throw_piece(algorithms::m2_edges::DR); break;
                        case blue:{
                            if (parity)
                                solution += throw_piece(algorithms::m2_edges::UF);
                            else
                                solution += throw_piece(algorithms::m2_edges::DB);
                            } break;
                        case magenta:
                            solution += throw_piece(algorithms::m2_edges::DL); break;
                    } break;
            }
        }
        // If the buffer piece is in its position, throw in the first
        // unsolved sticker we find
        else{
            if (cube_ref.FU() != cube_ref.Fc())
                solution += throw_piece(algorithms::m2_edges::FU);
            else if (cube_ref.RU() != cube_ref.Rc())
                solution += throw_piece(algorithms::m2_edges::RU);
            else if (cube_ref.RF() != cube_ref.Rc())
                solution += throw_piece(algorithms::m2_edges::RF);
            else if (cube_ref.RD() != cube_ref.Rc())
                solution += throw_piece(algorithms::m2_edges::RD);
            else if (cube_ref.RB() != cube_ref.Rc())
                solution += throw_piece(algorithms::m2_edges::RB);
            else if (cube_ref.BD() != cube_ref.Bc())
                solution += throw_piece(algorithms::m2_edges::BD);
            else if (cube_ref.LU() != cube_ref.Lc())
                solution += throw_piece(algorithms::m2_edges::LU);
            else if (cube_ref.LB() != cube_ref.Lc())
                solution += throw_piece(algorithms::m2_edges::LB);
            else if (cube_ref.LD() != cube_ref.Lc())
                solution += throw_piece(algorithms::m2_edges::LD);
            else if (cube_ref.LF() != cube_ref.Lc())
                solution += throw_piece(algorithms::m2_edges::LF);
            else if (cube_ref.DB() != cube_ref.Dc())
                solution += throw_piece(algorithms::m2_edges::DB);

            else if (parity){
                if (cube_ref.FL() != cube_ref.Bc())
                    solution += throw_piece(algorithms::m2_edges::FL);
                else if (cube_ref.FR() != cube_ref.Bc())
                    solution += throw_piece(algorithms::m2_edges::FR);
                else if (cube_ref.BU() != cube_ref.Fc())
                    solution += throw_piece(algorithms::m2_edges::BU);
                else if (cube_ref.BR() != cube_ref.Fc())
                    solution += throw_piece(algorithms::m2_edges::BR);
                else if (cube_ref.BL() != cube_ref.Fc())
                    solution += throw_piece(algorithms::m2_edges::BL);
                else if (cube_ref.DR() != cube_ref.Uc())
                    solution += throw_piece(algorithms::m2_edges::DR);
                else
                    solution += throw_piece(algorithms::m2_edges::DL);
            }
            else{
                if (cube_ref.FL() != cube_ref.Fc())
                    solution += throw_piece(algorithms::m2_edges::FL);
                else if (cube_ref.FR() != cube_ref.Fc())
                    solution += throw_piece(algorithms::m2_edges::FR);
                else if (cube_ref.BU() != cube_ref.Bc())
                    solution += throw_piece(algorithms::m2_edges::BU);
                else if (cube_ref.BR() != cube_ref.Bc())
                    solution += throw_piece(algorithms::m2_edges::BR);
                else if (cube_ref.BL() != cube_ref.Bc())
                    solution += throw_piece(algorithms::m2_edges::BL);
                else if (cube_ref.DR() != cube_ref.Dc())
                    solution += throw_piece(algorithms::m2_edges::DR);
                else
                    solution += throw_piece(algorithms::m2_edges::DL);
            }
        }
    }

    return cancel_moves(solution);
}
