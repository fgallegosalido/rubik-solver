#include <algorithm>

#include "cube_algorithms.hpp"
#include "old_pochmann_edges.hpp"
#include "utilities.hpp"

#pragma GCC diagnostic ignored "-Wswitch"

void OldPochmannEdges::change_parity(){
    parity = !parity;
}

const bool& OldPochmannEdges::is_parity() const{
    return parity;
}

std::string OldPochmannEdges::throw_piece(const std::string &conjugation){
    cube_ref << conjugation
             << algorithms::old_pochmann_edges::Ex
             << inverse_algorithm(conjugation);

    change_parity();

    return conjugation + " "
         + algorithms::old_pochmann_edges::Ex + " "
         + inverse_algorithm(conjugation) + " ";
}

bool OldPochmannEdges::is_solved() const{
    return std::all_of(cube_ref.begin(), std::prev(cube_ref.end()), [](const auto& face){
        return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
    });
}

std::string OldPochmannEdges::solve(){
    std::string solution;

    while (!is_solved()){
        // First we check that the piece in the buffer is not in its position
        if ((cube_ref.UR()!=cube_ref.Uc() || cube_ref.RU()!=cube_ref.Rc()) &&
            (cube_ref.UR()!=cube_ref.Rc() || cube_ref.RU()!=cube_ref.Uc())){
            // Checks the buffer piece and throws it to its correct position
            if (cube_ref.UR() == cube_ref.Uc()){
                if (cube_ref.RU() == cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_edges::UF);
                else if (cube_ref.RU() == cube_ref.Bc())
                    solution += throw_piece(algorithms::old_pochmann_edges::UB);
                else if (cube_ref.RU() == cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_edges::UL);
            }
            if (cube_ref.UR() == cube_ref.Fc()){
                if (cube_ref.RU() == cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_edges::FU);
                else if (cube_ref.RU() == cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_edges::FL);
                else if (cube_ref.RU() == cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_edges::FD);
                else if (cube_ref.RU() == cube_ref.Rc())
                    solution += throw_piece(algorithms::old_pochmann_edges::FR);
            }
            if (cube_ref.UR() == cube_ref.Rc()){
                if (cube_ref.RU() == cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_edges::RF);
                else if (cube_ref.RU() == cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_edges::RD);
                else if (cube_ref.RU() == cube_ref.Bc())
                    solution += throw_piece(algorithms::old_pochmann_edges::RB);
            }
            if (cube_ref.UR() == cube_ref.Bc()){
                if (cube_ref.RU() == cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_edges::BU);
                else if (cube_ref.RU() == cube_ref.Rc())
                    solution += throw_piece(algorithms::old_pochmann_edges::BR);
                else if (cube_ref.RU() == cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_edges::BD);
                else if (cube_ref.RU() == cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_edges::BL);
            }
            if (cube_ref.UR() == cube_ref.Lc()){
                if (cube_ref.RU() == cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_edges::LU);
                else if (cube_ref.RU() == cube_ref.Bc())
                    solution += throw_piece(algorithms::old_pochmann_edges::LB);
                else if (cube_ref.RU() == cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_edges::LD);
                else if (cube_ref.RU() == cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_edges::LF);
            }
            if (cube_ref.UR() == cube_ref.Dc()){
                if (cube_ref.RU() == cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_edges::DF);
                else if (cube_ref.RU() == cube_ref.Rc())
                    solution += throw_piece(algorithms::old_pochmann_edges::DR);
                else if (cube_ref.RU() == cube_ref.Bc())
                    solution += throw_piece(algorithms::old_pochmann_edges::DB);
                else if (cube_ref.RU() == cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_edges::DL);
            }
        }
        // If the buffer piece is in its position, throw in the first
        // unsolved sticker we find
        else{
            if (cube_ref.FU() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_edges::FU);
            else if (cube_ref.FL() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_edges::FL);
            else if (cube_ref.FD() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_edges::FD);
            else if (cube_ref.FR() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_edges::FR);
            else if (cube_ref.RF() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_edges::RF);
            else if (cube_ref.RD() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_edges::RD);
            else if (cube_ref.RB() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_edges::RB);
            else if (cube_ref.BU() != cube_ref.Bc())
                solution += throw_piece(algorithms::old_pochmann_edges::BU);
            else if (cube_ref.BR() != cube_ref.Bc())
                solution += throw_piece(algorithms::old_pochmann_edges::BR);
            else if (cube_ref.BD() != cube_ref.Bc())
                solution += throw_piece(algorithms::old_pochmann_edges::BD);
            else if (cube_ref.BL() != cube_ref.Bc())
                solution += throw_piece(algorithms::old_pochmann_edges::BL);
            else if (cube_ref.LU() != cube_ref.Lc())
                solution += throw_piece(algorithms::old_pochmann_edges::LU);
            else if (cube_ref.LB() != cube_ref.Lc())
                solution += throw_piece(algorithms::old_pochmann_edges::LB);
            else if (cube_ref.LD() != cube_ref.Lc())
                solution += throw_piece(algorithms::old_pochmann_edges::LD);
            else if (cube_ref.LF() != cube_ref.Lc())
                solution += throw_piece(algorithms::old_pochmann_edges::LF);
            else if (cube_ref.DF() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_edges::DF);
            else if (cube_ref.DR() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_edges::DR);
            else if (cube_ref.DB() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_edges::DB);
            else
                solution += throw_piece(algorithms::old_pochmann_edges::DL);
        }
    }

    return cancel_moves(solution);
}
