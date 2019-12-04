#include "cross.hpp"

#include <iostream>
#include <array>
#include <iterator>
#include <numeric>

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

bool Cross::solve_impl(unsigned depth, std::vector<std::string_view> &v, const Cube &original){
    using namespace std::literals::string_view_literals;

    static constexpr std::array moves{
        "U"sv, "F"sv, "R"sv, "B"sv, "L"sv, "D"sv,
        "U'"sv, "F'"sv, "R'"sv, "B'"sv, "L'"sv, "D'"sv,
        "U2"sv, "F2"sv, "R2"sv, "B2"sv, "L2"sv, "D2"sv
    };

    if (depth == 0){
        for (const auto &move : v){
            cube_ref << move;
        }

        if (is_solved())
            return true;

        cube_ref = original;
    }
    else if (v.size() == 0){
        for (const auto &move : moves){
            v.push_back(move);

            if (solve_impl(depth-1, v, original))
                return true;

            v.pop_back();
        }
    }
    else if (v.size() == 1){
        for (const auto &move : moves){
            if (move[0] != v.back()[0]){
                v.push_back(move);

                if (solve_impl(depth-1, v, original))
                    return true;

                v.pop_back();
            }
        }
    }
    else if (v.size() > 1){
        for (const auto &move : moves){
            if (move[0] != v.back()[0]){
                if (move[0] != v[v.size()-2][0] || !is_opposite(move, v.back())){
                    v.push_back(move);

                    if (solve_impl(depth-1, v, original))
                        return true;

                    v.pop_back();
                }
            }
        }
    }

    return false;
}

std::string Cross::solve(){
    std::vector<std::string_view> moves_list;
    const Cube original{cube_ref};

    for (unsigned i=0; !is_solved(); ++i){
        solve_impl(i, moves_list, original);
    }

    return (moves_list.empty()) ? "" : cancel_moves(
        std::accumulate(
            std::next(moves_list.begin()),
            moves_list.end(),
            std::string{moves_list.begin()->data()},
            [](const auto &acc, const auto &rhs){
                return (acc + ' ') + rhs.data();
            }
        )
    );
}
