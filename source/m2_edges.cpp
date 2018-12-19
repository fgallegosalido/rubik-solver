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

        return std::all_of(aux.begin(), std::prev(aux.end()), [](const auto& face){
            return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
        });
    }
    else{
        return std::all_of(cube_ref.begin(), std::prev(cube_ref.end()), [](const auto& face){
            return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
        });
    }
}

std::string M2Edges::solve(){
    // Variable that will hold the final solution
    std::string solution;

    while (!is_solved()){
        // In order to check pieces, we need to know the current parity
        if (parity){
            // First we check that the piece in the buffer is not in its position
            if ((cube_ref.FD()!=cube_ref.Bc() || cube_ref.DF()!=cube_ref.Uc()) &&
                (cube_ref.FD()!=cube_ref.Uc() || cube_ref.DF()!=cube_ref.Bc())){
                // Checks the buffer piece and throws it to its correct position
                if (cube_ref.DF() == cube_ref.Dc()){
                    if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::DB);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::UR);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::UB);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::UL);
                }
                if (cube_ref.DF() == cube_ref.Bc()){
                    if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::BD);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::FL);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::FR);
                }
                if (cube_ref.DF() == cube_ref.Rc()){
                    if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::RU);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::RF);
                    else if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::RD);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::RB);
                }
                if (cube_ref.DF() == cube_ref.Fc()){
                    if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::BU);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::BR);
                    else if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::FU);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::BL);
                }
                if (cube_ref.DF() == cube_ref.Lc()){
                    if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::LU);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::LB);
                    else if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::LD);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::LF);
                }
                if (cube_ref.DF() == cube_ref.Uc()){
                    if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::DR);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::UF);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::DL);
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
                else if (cube_ref.FL() != cube_ref.Bc())
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
        }
        else{
            // First we check that the piece in the buffer is not in its position
            if ((cube_ref.FD()!=cube_ref.Fc() || cube_ref.DF()!=cube_ref.Dc()) &&
                (cube_ref.FD()!=cube_ref.Dc() || cube_ref.DF()!=cube_ref.Fc())){
                // Checks the buffer piece and throws it to its correct position
                if (cube_ref.DF() == cube_ref.Uc()){
                    if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::UF);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::UR);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::UB);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::UL);
                }
                if (cube_ref.DF() == cube_ref.Fc()){
                    if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::FU);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::FL);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::FR);
                }
                if (cube_ref.DF() == cube_ref.Rc()){
                    if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::RU);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::RF);
                    else if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::RD);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::RB);
                }
                if (cube_ref.DF() == cube_ref.Bc()){
                    if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::BU);
                    else if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::BR);
                    else if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::BD);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::BL);
                }
                if (cube_ref.DF() == cube_ref.Lc()){
                    if (cube_ref.FD() == cube_ref.Uc())
                        solution += throw_piece(algorithms::m2_edges::LU);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::LB);
                    else if (cube_ref.FD() == cube_ref.Dc())
                        solution += throw_piece(algorithms::m2_edges::LD);
                    else if (cube_ref.FD() == cube_ref.Fc())
                        solution += throw_piece(algorithms::m2_edges::LF);
                }
                if (cube_ref.DF() == cube_ref.Dc()){
                    if (cube_ref.FD() == cube_ref.Rc())
                        solution += throw_piece(algorithms::m2_edges::DR);
                    else if (cube_ref.FD() == cube_ref.Bc())
                        solution += throw_piece(algorithms::m2_edges::DB);
                    else if (cube_ref.FD() == cube_ref.Lc())
                        solution += throw_piece(algorithms::m2_edges::DL);
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
                else if (cube_ref.FL() != cube_ref.Fc())
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
