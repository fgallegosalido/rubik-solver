#include <algorithm>

#include "old_pochmann_edges.hpp"
#include "utilities.hpp"

#pragma GCC diagnostic ignored "-Wswitch"

void OldPochmannEdges::change_parity(){
    parity = !parity;
}

const bool& OldPochmannEdges::is_parity() const{
    return parity;
}

std::string OldPochmannEdges::orientate_cube(){
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

std::string OldPochmannEdges::throw_piece(const std::string &conjugation){
    cube_ref << conjugation
             << algorithms::old_pochmann_edges::Ex
             << inverse_algorithm(conjugation);

    change_parity();

    return conjugation + " "
         + algorithms::old_pochmann_edges::Ex + " "
         + inverse_algorithm(conjugation) + " ";
}

bool OldPochmannEdges::method_finished() const{
    return std::all_of(cube_ref.begin(), cube_ref.end()-1, [](const auto& face){
        return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
    });
}

std::string OldPochmannEdges::apply_method(){
    // Variable that will hold the final solution
    auto solution = orientate_cube();

    while (!method_finished()){
        // First we check that the piece in the buffer is not in its position
        if ((cube_ref.UR()!=white || cube_ref.RU()!=red) && (cube_ref.UR()!=red || cube_ref.RU()!=white)){
            // Checks the buffer piece and throws it to its correct position
            switch (cube_ref.UR()){
                case white:
                    switch (cube_ref.RU()) {
                        case green:
                            solution += throw_piece(algorithms::old_pochmann_edges::UF); break;
                        case blue:
                            solution += throw_piece(algorithms::old_pochmann_edges::UB); break;
                        case magenta:
                            solution += throw_piece(algorithms::old_pochmann_edges::UL); break;
                    } break;
                case green:
                    switch (cube_ref.RU()){
                        case white:
                            solution += throw_piece(algorithms::old_pochmann_edges::FU); break;
                        case magenta:
                            solution += throw_piece(algorithms::old_pochmann_edges::FL); break;
                        case yellow:
                            solution += throw_piece(algorithms::old_pochmann_edges::FD); break;
                        case red:
                            solution += throw_piece(algorithms::old_pochmann_edges::FR); break;
                    } break;
                case red:
                    switch (cube_ref.RU()){
                        case green:
                            solution += throw_piece(algorithms::old_pochmann_edges::RF); break;
                        case yellow:
                            solution += throw_piece(algorithms::old_pochmann_edges::RD); break;
                        case blue:
                            solution += throw_piece(algorithms::old_pochmann_edges::RB); break;
                    } break;
                case blue:
                    switch (cube_ref.RU()){
                        case white:
                            solution += throw_piece(algorithms::old_pochmann_edges::BU); break;
                        case red:
                            solution += throw_piece(algorithms::old_pochmann_edges::BR); break;
                        case yellow:
                            solution += throw_piece(algorithms::old_pochmann_edges::BD); break;
                        case magenta:
                            solution += throw_piece(algorithms::old_pochmann_edges::BL); break;
                    } break;
                case magenta:
                    switch (cube_ref.RU()){
                        case white:
                            solution += throw_piece(algorithms::old_pochmann_edges::LU); break;
                        case blue:
                            solution += throw_piece(algorithms::old_pochmann_edges::LB); break;
                        case yellow:
                            solution += throw_piece(algorithms::old_pochmann_edges::LD); break;
                        case green:
                            solution += throw_piece(algorithms::old_pochmann_edges::LF); break;
                    } break;
                case yellow:
                    switch (cube_ref.RU()){
                        case green:
                            solution += throw_piece(algorithms::old_pochmann_edges::DF); break;
                        case red:
                            solution += throw_piece(algorithms::old_pochmann_edges::DR); break;
                        case blue:
                            solution += throw_piece(algorithms::old_pochmann_edges::DB); break;
                        case magenta:
                            solution += throw_piece(algorithms::old_pochmann_edges::DL); break;
                    } break;
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
