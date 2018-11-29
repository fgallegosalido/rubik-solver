#include <algorithm>

#include "old_pochmann_edges.hpp"
#include "utilities.hpp"

#pragma GCC diagnostic ignored "-Wswitch"

void OldPochmannEdges::orientate_cube(){
    if (cube_ref.Fc() == white)
        cube_ref.x();
    else if (cube_ref.Rc() == white)
        cube_ref.zz();
    else if (cube_ref.Bc() == white)
        cube_ref.xx();
    else if (cube_ref.Lc() == white)
        cube_ref.z();
    else if (cube_ref.Dc() == white)
        cube_ref.x2();

    if (cube_ref.Rc() == green)
        cube_ref.y();
    else if (cube_ref.Bc() == green)
        cube_ref.y2();
    else if (cube_ref.Lc() == green)
        cube_ref.yy();
}

void OldPochmannEdges::throw_piece(const char* conjugation){
    cube_ref.read_algorithm(conjugation);
    cube_ref.read_algorithm(algorithms::old_pochmann_edges::Ex);
    cube_ref.read_algorithm(inverse_algorithm(conjugation));
}

bool OldPochmannEdges::method_finished(){
    return std::all_of(cube_ref.begin(), cube_ref.end()-1, [](const auto& face){
        return face[1] == face[3] && face[3] == face[5] && face[5] == face[7];
    });
}

std::string OldPochmannEdges::apply_method(){
    orientate_cube();

    while (!method_finished()){
        if ((cube_ref.UR()!=white || cube_ref.RU()!=red) && (cube_ref.UR()!=red || cube_ref.RU()!=white)){
            switch (cube_ref.UR()){
                case white:
                    switch (cube_ref.RU()) {
                        case green:
                            throw_piece(algorithms::old_pochmann_edges::UF); break;
                        case blue:
                            throw_piece(algorithms::old_pochmann_edges::UB); break;
                        case magenta:
                            throw_piece(algorithms::old_pochmann_edges::UL); break;
                    } break;
                case green:
                    switch (cube_ref.RU()){
                        case white:
                            throw_piece(algorithms::old_pochmann_edges::FU); break;
                        case magenta:
                            throw_piece(algorithms::old_pochmann_edges::FL); break;
                        case yellow:
                            throw_piece(algorithms::old_pochmann_edges::FD); break;
                        case red:
                            throw_piece(algorithms::old_pochmann_edges::FR); break;
                    } break;
                case red:
                    switch (cube_ref.RU()){
                        case green:
                            throw_piece(algorithms::old_pochmann_edges::RF); break;
                        case yellow:
                            throw_piece(algorithms::old_pochmann_edges::RD); break;
                        case blue:
                            throw_piece(algorithms::old_pochmann_edges::RB); break;
                    } break;
                case blue:
                    switch (cube_ref.RU()){
                        case white:
                            throw_piece(algorithms::old_pochmann_edges::BU); break;
                        case red:
                            throw_piece(algorithms::old_pochmann_edges::BR); break;
                        case yellow:
                            throw_piece(algorithms::old_pochmann_edges::BD); break;
                        case magenta:
                            throw_piece(algorithms::old_pochmann_edges::BL); break;
                    } break;
                case magenta:
                    switch (cube_ref.RU()){
                        case white:
                            throw_piece(algorithms::old_pochmann_edges::LU); break;
                        case blue:
                            throw_piece(algorithms::old_pochmann_edges::LB); break;
                        case yellow:
                            throw_piece(algorithms::old_pochmann_edges::LD); break;
                        case green:
                            throw_piece(algorithms::old_pochmann_edges::LF); break;
                    } break;
                case yellow:
                    switch (cube_ref.RU()){
                        case green:
                            throw_piece(algorithms::old_pochmann_edges::DF); break;
                        case red:
                            throw_piece(algorithms::old_pochmann_edges::DR); break;
                        case blue:
                            throw_piece(algorithms::old_pochmann_edges::DB); break;
                        case magenta:
                            throw_piece(algorithms::old_pochmann_edges::DL); break;
                    } break;
            }
        }
        else{
            if (cube_ref.FU() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_edges::FU);
            else if (cube_ref.FL() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_edges::FL);
            else if (cube_ref.FD() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_edges::FD);
            else if (cube_ref.FR() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_edges::FR);
            else if (cube_ref.BU() != cube_ref.Bc())
                throw_piece(algorithms::old_pochmann_edges::BU);
            else if (cube_ref.BR() != cube_ref.Bc())
                throw_piece(algorithms::old_pochmann_edges::BR);
            else if (cube_ref.BD() != cube_ref.Bc())
                throw_piece(algorithms::old_pochmann_edges::BD);
            else if (cube_ref.BL() != cube_ref.Bc())
                throw_piece(algorithms::old_pochmann_edges::BL);
            else if (cube_ref.LU() != cube_ref.Lc())
                throw_piece(algorithms::old_pochmann_edges::LU);
            else if (cube_ref.LB() != cube_ref.Lc())
                throw_piece(algorithms::old_pochmann_edges::LB);
            else if (cube_ref.LD() != cube_ref.Lc())
                throw_piece(algorithms::old_pochmann_edges::LD);
            else if (cube_ref.LF() != cube_ref.Lc())
                throw_piece(algorithms::old_pochmann_edges::LF);
            else if (cube_ref.DF() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_edges::DF);
            else if (cube_ref.DR() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_edges::DR);
            else if (cube_ref.DB() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_edges::DB);
            else
                throw_piece(algorithms::old_pochmann_edges::DL);
        }
    }
    return "";
}
