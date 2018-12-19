#include <algorithm>
#include <array>

#include "cube_algorithms.hpp"
#include "old_pochmann_corners.hpp"
#include "utilities.hpp"

void OldPochmannCorners::change_parity(){
    parity = !parity;
}

const bool& OldPochmannCorners::is_parity() const{
    return parity;
}

// This function throws the buffer piece to a specific position
std::string OldPochmannCorners::throw_piece(const std::string &conjugation){
    cube_ref << conjugation
             << algorithms::old_pochmann_corners::Ex
             << inverse_algorithm(conjugation);

    change_parity();

    return conjugation                          + " "
         + algorithms::old_pochmann_corners::Ex + " "
         + inverse_algorithm(conjugation)       + " ";
}

// Just check if the corners are solved
bool OldPochmannCorners::is_solved() const{
    return std::all_of(cube_ref.begin(), std::prev(cube_ref.end(), 2), [](const auto& face){
        return face[0] == face[2] && face[2] == face[6] && face[6] == face[8];
    });
}

std::string OldPochmannCorners::solve(){
    // Variable that will hold the final solution
    std::string solution;

    while (!is_solved()){
        std::array<color, 3> buffer = {cube_ref.ULB(), cube_ref.LBU(), cube_ref.BUL()};

        // First we check if the piece in the buffer is not in its position
        if (!std::is_permutation(buffer.begin(), buffer.end(),
            std::array{cube_ref.Uc(), cube_ref.Lc(), cube_ref.Bc()}.begin())){
            // Here we check the piece we want to throw and throw it to its
            // correct position
            if (buffer[0] == cube_ref.Uc()){
                if (buffer[1]==cube_ref.Fc() && buffer[2]==cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_corners::UFL);
                else if (buffer[1]==cube_ref.Rc() && buffer[2]==cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_corners::URF);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::UBR);
            }
            else if (buffer[0] == cube_ref.Fc()){
                if (buffer[1]==cube_ref.Lc() && buffer[2]==cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_corners::FLU);
                else if (buffer[1]==cube_ref.Dc() && buffer[2]==cube_ref.Lc())
                    solution += throw_piece(algorithms::old_pochmann_corners::FDL);
                else if (buffer[1]==cube_ref.Rc() && buffer[2]==cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_corners::FRD);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::FUR);
            }
            else if (buffer[0] == cube_ref.Rc()){
                if (buffer[1]==cube_ref.Fc() && buffer[2]==cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_corners::RFU);
                else if (buffer[1]==cube_ref.Dc() && buffer[2]==cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_corners::RDF);
                else if (buffer[1]==cube_ref.Bc() && buffer[2]==cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_corners::RBD);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::RUB);
            }
            else if (buffer[0] == cube_ref.Bc()){
                if (buffer[1]==cube_ref.Rc() && buffer[2]==cube_ref.Uc())
                    solution += throw_piece(algorithms::old_pochmann_corners::BRU);
                else if (buffer[1]==cube_ref.Dc() && buffer[2]==cube_ref.Rc())
                    solution += throw_piece(algorithms::old_pochmann_corners::BDR);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::BLD);
            }
            else if (buffer[0] == cube_ref.Lc()){
                if (buffer[1]==cube_ref.Uc() && buffer[2]==cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_corners::LUF);
                else if (buffer[1]==cube_ref.Fc() && buffer[2]==cube_ref.Dc())
                    solution += throw_piece(algorithms::old_pochmann_corners::LFD);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::LDB);
            }
            else if (buffer[0] == cube_ref.Dc()){
                if (buffer[1]==cube_ref.Lc() && buffer[2]==cube_ref.Fc())
                    solution += throw_piece(algorithms::old_pochmann_corners::DLF);
                else if (buffer[1]==cube_ref.Fc() && buffer[2]==cube_ref.Rc())
                    solution += throw_piece(algorithms::old_pochmann_corners::DFR);
                else if (buffer[1]==cube_ref.Rc() && buffer[2]==cube_ref.Bc())
                    solution += throw_piece(algorithms::old_pochmann_corners::DRB);
                else
                    solution += throw_piece(algorithms::old_pochmann_corners::DBL);
            }
        }
        // If the piece in the buffer is in its position, we just throw it
        // whatever first unsolved sticker we find
        else{
            if (cube_ref.FLU() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_corners::FLU);
            else if (cube_ref.FUR() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_corners::FUR);
            else if (cube_ref.FRD() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_corners::FRD);
            else if (cube_ref.FDL() != cube_ref.Fc())
                solution += throw_piece(algorithms::old_pochmann_corners::FDL);
            else if (cube_ref.RFU() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_corners::RFU);
            else if (cube_ref.RUB() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_corners::RUB);
            else if (cube_ref.RBD() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_corners::RBD);
            else if (cube_ref.RDF() != cube_ref.Rc())
                solution += throw_piece(algorithms::old_pochmann_corners::RDF);
            else if (cube_ref.DLF() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_corners::DLF);
            else if (cube_ref.DFR() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_corners::DFR);
            else if (cube_ref.DRB() != cube_ref.Dc())
                solution += throw_piece(algorithms::old_pochmann_corners::DRB);
            else
                solution += throw_piece(algorithms::old_pochmann_corners::DBL);
        }
    }

    return cancel_moves(solution);
}
