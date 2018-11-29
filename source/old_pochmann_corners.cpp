#include <algorithm>
#include <array>

#include "old_pochmann_corners.hpp"
#include "utilities.hpp"

// To apply the method, the cube must be up-white and front-green
std::string OldPochmannCorners::orientate_cube(){
    std::string orientation;

    if (cube_ref.Fc() == white){
        cube_ref.x();
        orientation += "x ";
    }
    else if (cube_ref.Rc() == white){
        cube_ref.zz();
        orientation += "z' ";
    }
    else if (cube_ref.Bc() == white){
        cube_ref.xx();
        orientation += "x' ";
    }
    else if (cube_ref.Lc() == white){
        cube_ref.z();
        orientation += "z ";
    }
    else if (cube_ref.Dc() == white){
        cube_ref.x2();
        orientation += "x2 ";
    }

    if (cube_ref.Rc() == green){
        cube_ref.y();
        orientation += "y ";
    }
    else if (cube_ref.Bc() == green){
        cube_ref.y2();
        orientation += "y2 ";
    }
    else if (cube_ref.Lc() == green){
        cube_ref.yy();
        orientation += "y' ";
    }

    return orientation;
}

// This function throws the buffer piece to a specific position
std::string OldPochmannCorners::throw_piece(const std::string &conjugation){
    cube_ref.read_algorithm(conjugation);
    cube_ref.read_algorithm(algorithms::old_pochmann_corners::Ex);
    cube_ref.read_algorithm(inverse_algorithm(conjugation));

    return conjugation + " "
            + algorithms::old_pochmann_corners::Ex + " "
            + inverse_algorithm(conjugation) + " ";
}

// Just check if the corners are solved
bool OldPochmannCorners::method_finished(){
    return std::all_of(cube_ref.begin(), cube_ref.end()-2, [](const auto& face){
        return face[0] == face[2] && face[2] == face[6] && face[6] == face[8];
    });
}

std::string OldPochmannCorners::apply_method(){
    // Variable that will hold the final solution
    auto solution = orientate_cube();

    while (!method_finished()){
        std::array<color, 3> buffer = {cube_ref.ULB(), cube_ref.LBU(), cube_ref.BUL()};

        // First we check if the piece in the buffer is not in its position
        if (!std::is_permutation(buffer.begin(), buffer.end(), std::array{white, magenta, blue}.begin())){
            // Here we check the piece we want to throw and throw it to its
            // correct position
            switch (buffer[0]){
                case white:
                    if (buffer[1]==green && buffer[2]==magenta)
                        solution += throw_piece(algorithms::old_pochmann_corners::UFL);
                    else if (buffer[1]==red && buffer[2]==green)
                        solution += throw_piece(algorithms::old_pochmann_corners::URF);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::UBR);
                    break;
                case green:
                    if (buffer[1]==magenta && buffer[2]==white)
                        solution += throw_piece(algorithms::old_pochmann_corners::FLU);
                    else if (buffer[1]==yellow && buffer[2]==magenta)
                        solution += throw_piece(algorithms::old_pochmann_corners::FDL);
                    else if (buffer[1]==red && buffer[2]==yellow)
                        solution += throw_piece(algorithms::old_pochmann_corners::FRD);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::FUR);
                    break;
                case red:
                    if (buffer[1]==green && buffer[2]==white)
                        solution += throw_piece(algorithms::old_pochmann_corners::RFU);
                    else if (buffer[1]==yellow && buffer[2]==green)
                        solution += throw_piece(algorithms::old_pochmann_corners::RDF);
                    else if (buffer[1]==blue && buffer[2]==yellow)
                        solution += throw_piece(algorithms::old_pochmann_corners::RBD);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::RUB);
                    break;
                case blue:
                    if (buffer[1]==red && buffer[2]==white)
                        solution += throw_piece(algorithms::old_pochmann_corners::BRU);
                    else if (buffer[1]==yellow && buffer[2]==red)
                        solution += throw_piece(algorithms::old_pochmann_corners::BDR);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::BLD);
                    break;
                case magenta:
                    if (buffer[1]==white && buffer[2]==green)
                        solution += throw_piece(algorithms::old_pochmann_corners::LUF);
                    else if (buffer[1]==green && buffer[2]==yellow)
                        solution += throw_piece(algorithms::old_pochmann_corners::LFD);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::LDB);
                    break;
                case yellow:
                    if (buffer[1]==magenta && buffer[2]==green)
                        solution += throw_piece(algorithms::old_pochmann_corners::DLF);
                    else if (buffer[1]==green && buffer[2]==red)
                        solution += throw_piece(algorithms::old_pochmann_corners::DFR);
                    else if (buffer[1]==red && buffer[2]==blue)
                        solution += throw_piece(algorithms::old_pochmann_corners::DRB);
                    else
                        solution += throw_piece(algorithms::old_pochmann_corners::DBL);
                    break;
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

    solution.pop_back();    // Gets rid of the last space
    return solution;
}
