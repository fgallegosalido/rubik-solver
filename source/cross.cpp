#include <deque>
#include <string>

#include "cross.hpp"
#include "utilities.hpp"

bool Cross::is_solved() const{
    return cube_ref.UF() == cube_ref.UR() &&
           cube_ref.UR() == cube_ref.UB() &&
           cube_ref.UB() == cube_ref.UL() &&
           cube_ref.UL() == cube_ref.Uc() &&
           cube_ref.FU() == cube_ref.Fc() &&
           cube_ref.RU() == cube_ref.Rc() &&
           cube_ref.BU() == cube_ref.Bc() &&
           cube_ref.LU() == cube_ref.Lc();
}

namespace {
    std::array<const char*, 18> moves{"U", "F", "R", "B", "L", "D",
                                      "U'", "F'", "R'", "B'", "L'", "D'",
                                      "U2", "F2", "R2", "B2", "L2", "D2"};
}

void Cross::solve_impl(std::deque<std::string> &solution, unsigned depth){
    if (depth==8){
        for (const auto &move : moves){
            cube_ref << move;

            if (is_solved()){
                solution.emplace_back(move);
                break;
            }

            cube_ref << inverse_algorithm(move);
        }
    }
    else{
        for (const auto &move : moves){
            if (!solution.empty() && solution.back()[0]==move[0])
                continue;

            cube_ref << move;
            solution.emplace_back(move);

            if (is_solved())
                break;
            else{
                solve_impl(solution, depth+1);

                if (is_solved())
                    break;
            }

            cube_ref << inverse_algorithm(move);
            solution.pop_back();
        }
    }
}

std::string Cross::solve(){
    std::string solution;

    if (!is_solved()){
        std::deque<std::string> moves_list;
        solve_impl(moves_list, 1);

        for (const auto &move : moves_list)
            solution += move + " ";
    }

    if (!solution.empty())
        solution.pop_back();

    return cancel_moves(solution);
}
