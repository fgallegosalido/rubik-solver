#include <algorithm>
#include <array>

#include "old_pochmann_corners.hpp"
#include "utilities.hpp"

void OldPochmannCorners::orientate_cube(){
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

void OldPochmannCorners::throw_piece(const char* commutator){
    cube_ref.read_algorithm(commutator);
    cube_ref.read_algorithm(algorithms::old_pochmann_corners::Ex);
    cube_ref.read_algorithm(inverse_algorithm(commutator));
}

bool OldPochmannCorners::method_finished(){
    return std::all_of(cube_ref.begin(), cube_ref.end()-2, [](const auto& face){
        return face[0] == face[2] && face[2] == face[6] && face[6] == face[8];
    });
}

void OldPochmannCorners::apply_method(){
    orientate_cube();

    while (!method_finished()){
        //LOG(cube_ref);

        std::array<color, 3> buffer = {cube_ref.ULB(), cube_ref.LBU(), cube_ref.BUL()};

        if (!std::is_permutation(buffer.begin(), buffer.end(), std::array{white, magenta, blue}.begin())){
            switch (buffer[0]){
                case white:
                    if (buffer[1]==green && buffer[2]==magenta)
                        throw_piece(algorithms::old_pochmann_corners::UFL);
                    else if (buffer[1]==red && buffer[2]==green)
                        throw_piece(algorithms::old_pochmann_corners::URF);
                    else
                        throw_piece(algorithms::old_pochmann_corners::UBR);
                    break;
                case green:
                    if (buffer[1]==magenta && buffer[2]==white)
                        throw_piece(algorithms::old_pochmann_corners::FLU);
                    else if (buffer[1]==yellow && buffer[2]==magenta)
                        throw_piece(algorithms::old_pochmann_corners::FDL);
                    else if (buffer[1]==red && buffer[2]==yellow)
                        throw_piece(algorithms::old_pochmann_corners::FRD);
                    else
                        throw_piece(algorithms::old_pochmann_corners::FUR);
                    break;
                case red:
                    if (buffer[1]==green && buffer[2]==white)
                        throw_piece(algorithms::old_pochmann_corners::RFU);
                    else if (buffer[1]==yellow && buffer[2]==green)
                        throw_piece(algorithms::old_pochmann_corners::RDF);
                    else if (buffer[1]==blue && buffer[2]==yellow)
                        throw_piece(algorithms::old_pochmann_corners::RBD);
                    else
                        throw_piece(algorithms::old_pochmann_corners::RUB);
                    break;
                case blue:
                    if (buffer[1]==red && buffer[2]==white)
                        throw_piece(algorithms::old_pochmann_corners::BRU);
                    else if (buffer[1]==yellow && buffer[2]==red)
                        throw_piece(algorithms::old_pochmann_corners::BDR);
                    else
                        throw_piece(algorithms::old_pochmann_corners::BLD);
                    break;
                case magenta:
                    if (buffer[1]==white && buffer[2]==green)
                        throw_piece(algorithms::old_pochmann_corners::LUF);
                    else if (buffer[1]==green && buffer[2]==yellow)
                        throw_piece(algorithms::old_pochmann_corners::LFD);
                    else
                        throw_piece(algorithms::old_pochmann_corners::LDB);
                    break;
                case yellow:
                    if (buffer[1]==magenta && buffer[2]==green)
                        throw_piece(algorithms::old_pochmann_corners::DLF);
                    else if (buffer[1]==green && buffer[2]==red)
                        throw_piece(algorithms::old_pochmann_corners::DFR);
                    else if (buffer[1]==red && buffer[2]==blue)
                        throw_piece(algorithms::old_pochmann_corners::DRB);
                    else
                        throw_piece(algorithms::old_pochmann_corners::DBL);
                    break;
            }
        }
        else{
            if (cube_ref.FLU() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_corners::FLU);
            else if (cube_ref.FUR() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_corners::FUR);
            else if (cube_ref.FRD() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_corners::FRD);
            else if (cube_ref.FDL() != cube_ref.Fc())
                throw_piece(algorithms::old_pochmann_corners::FDL);
            else if (cube_ref.RFU() != cube_ref.Rc())
                throw_piece(algorithms::old_pochmann_corners::RFU);
            else if (cube_ref.RUB() != cube_ref.Rc())
                throw_piece(algorithms::old_pochmann_corners::RUB);
            else if (cube_ref.RBD() != cube_ref.Rc())
                throw_piece(algorithms::old_pochmann_corners::RBD);
            else if (cube_ref.RDF() != cube_ref.Rc())
                throw_piece(algorithms::old_pochmann_corners::RDF);
            else if (cube_ref.DLF() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_corners::DLF);
            else if (cube_ref.DFR() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_corners::DFR);
            else if (cube_ref.DRB() != cube_ref.Dc())
                throw_piece(algorithms::old_pochmann_corners::DRB);
            else
                throw_piece(algorithms::old_pochmann_corners::DBL);
        }
    }
}
