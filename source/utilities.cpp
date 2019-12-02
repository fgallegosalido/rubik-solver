#include "utilities.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <cctype>

bool is_opposite(const std::string &lhs, const std::string &rhs){
    switch (lhs[0]){
        case 'U':
            return rhs[0] == 'D';
        case 'F':
            return rhs[0] == 'B';
        case 'R':
            return rhs[0] == 'L';
        case 'B':
            return rhs[0] == 'F';
        case 'L':
            return rhs[0] == 'R';
        case 'D':
            return rhs[0] == 'U';
        default:
            return false;
    }
}

std::string random_scramble(std::size_t length){
    if (length == 0)
        return std::string{""};

    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<unsigned> dis{0, 5};

    std::string scramble;

    constexpr std::array moves = {"U", "F", "R", "B", "L", "D"};
    constexpr std::array dirs = {"", "'", "2"};

    std::string next_move{moves[dis(gen)]};

    for (std::size_t i=0; i<length-1; ++i){
        scramble += next_move;
        next_move = moves[dis(gen)];

        while (scramble.back() == next_move[0])
            next_move = moves[dis(gen)];

        scramble += dirs[dis(gen)%3];
        scramble += " ";
    }

    scramble.pop_back();
    return scramble;
}

std::string parse_algorithm(const std::string &alg){
    std::istringstream ss{alg};
    std::string ret, turn;

    constexpr std::array moves = {
        'U', 'F', 'R', 'B', 'L', 'D',
        'u', 'f', 'r', 'b', 'l', 'd',
        'M', 'E', 'S', 'x', 'y', 'z'
    };

    while (ss >> turn)
        if (std::any_of(std::begin(moves), std::end(moves), [&turn](const auto &c){ return c == turn[0]; }))
            if (turn.size()==1 || (turn.size()==2 && (turn[1]=='\'' || turn[1]=='2')))
                ret += turn + ' ';

    return ret;
}

std::string inverse_algorithm(const std::string &alg){
    using namespace std::string_literals;

    std::string reverse_alg{parse_algorithm(alg)};
    std::reverse(reverse_alg.begin(), reverse_alg.end());

    std::istringstream ss{reverse_alg};
    std::string turn, ret;

    while (ss >> turn){
        if (turn.size() == 1)
            ret += turn + "' ";
        else if (turn.size() == 2){
            if (turn[0] == '\'')
                ret += turn.back() + " "s;
            else if (turn[0] == '2')
                ret += turn.back() + "2 "s;
        }
    }

    if (!ret.empty())
        ret.pop_back();

    return ret;
}

std::string cancel_moves(const std::string &alg){
    std::istringstream ss{parse_algorithm(alg)};
    std::string to_cancel, turn, ret;

    while (ss >> turn){
        if (to_cancel.empty())
            to_cancel = turn;
        else if (to_cancel[0] != turn[0]){
            ret += to_cancel + ' ';
            to_cancel = turn;
        }
        else if (to_cancel.size() == 1){
            if (turn.size() == 1)
                to_cancel += '2';
            else if (turn[1] == '\'')
                to_cancel = "";
            else if (turn[1] == '2')
                to_cancel += '\'';
        }
        else if (to_cancel[1] == '\''){
            if (turn.size() == 1)
                to_cancel = "";
            else if (turn[1] == '\'')
                to_cancel[1] = '2';
            else if (turn[1] == '2')
                to_cancel.pop_back();
        }
        else if (to_cancel[1] == '2'){
            if (turn.size() == 1)
                to_cancel[1] = '\'';
            else if (turn[1] == '\'')
                to_cancel.pop_back();
            else if (turn[1] == '2')
                to_cancel = "";
        }
    }

    if (!to_cancel.empty())
        ret += to_cancel;
    else if (!ret.empty())
        ret.pop_back();

    return ret;
}

std::size_t turn_count(const std::string &alg){
    std::istringstream ss{parse_algorithm(alg)};
    std::string t;
    std::size_t total = 0;

    constexpr std::array<char, 6> one_move{'U','F','R','B','L','D'};
    constexpr std::array<char, 3> two_moves{'M','S','E'};

    while (ss >> t){
        if (std::any_of(one_move.begin(), one_move.end(),
            [&t](const auto m){
                return std::toupper(t[0]) == m;
            }
        )) total += 1;

        else if (std::any_of(two_moves.begin(), two_moves.end(),
            [&t](const auto m){
                return std::toupper(t[0]) == m;
            }
        )) total += 2;
    }

    return total;
}


/* All the algorithm_to_canonical stuff (WIP)
namespace {
    // This function returns the turn but with the centers not changed
    std::string turn_to_canonical(const std::string &t){
        if (t[0]=='U' || t[0]=='R' || t[0]=='F' || t[0]=='D' || t[0]=='B' || t[0]=='L')
            return t;
        else if (t == "M")  return "L' R";
        else if (t == "M'") return "L R'";
        else if (t == "M2") return "L2 R2";
        else if (t == "E")  return "D' U";
        else if (t == "E'") return "D U'";
        else if (t == "E2") return "D2 U2";
        else if (t == "S")  return "F' B";
        else if (t == "S'") return "F B'";
        else if (t == "S2") return "F2 B2";
        else if (t == "u")  return "D";
        else if (t == "u'") return "D'";
        else if (t == "u2") return "D2";
        else if (t == "r")  return "L";
        else if (t == "r'") return "L'";
        else if (t == "r2") return "L2";
        else if (t == "f")  return "B";
        else if (t == "f'") return "B'";
        else if (t == "f2") return "B2";
        else if (t == "d")  return "U";
        else if (t == "d'") return "U'";
        else if (t == "d2") return "U2";
        else if (t == "b")  return "F";
        else if (t == "b'") return "F'";
        else if (t == "b2") return "F2";
        else if (t == "l")  return "R";
        else if (t == "l'") return "R'";
        else if (t == "l2") return "R2";
        else return "";
    }

    // This function returns the turn but relative to a cube rotation
    std::string turn_to_relative(const std::string &t, const std::string &rel_turn){
        if (rel_turn=="M'" || rel_turn=="r" || rel_turn=="l'" || rel_turn=="x"){

        }
        else if (rel_turn=="M" || rel_turn=="r'" || rel_turn=="l" || rel_turn=="x'"){

        }
        else if (rel_turn=="M2" || rel_turn=="r2" || rel_turn=="l2" || rel_turn=="x2"){

        }
        else if (rel_turn=="E'" || rel_turn=="u" || rel_turn=="d'" || rel_turn=="y"){

        }
        else if (rel_turn=="E" || rel_turn=="u'" || rel_turn=="d" || rel_turn=="y'"){

        }
        else if (rel_turn=="E2" || rel_turn=="u2" || rel_turn=="d2" || rel_turn=="y2"){

        }
        else if (rel_turn=="S" || rel_turn=="f" || rel_turn=="b'" || rel_turn=="z"){

        }
        else if (rel_turn=="S'" || rel_turn=="f'" || rel_turn=="b" || rel_turn=="z'"){

        }
        else if (rel_turn=="S2" || rel_turn=="f2" || rel_turn=="b2" || rel_turn=="z2"){

        }
        else return t; // Canonical turns don't change the centers
    }
}

std::string algorithm_to_canonical(const std::string& alg){
    std::istringstream ss{parse_algorithm(alg)};
    std::vector<std::string> moves {std::istream_iterator<std::string>{ss},
                                    std::istream_iterator<std::string>{}};
    std::string ret, turn;

    while (ss >> turn)
        moves.push_back(turn);

    for (auto it=moves.begin(); it!=moves.end(); ++it){
        std::transform(std::next(it), moves.end(), std::next(it),
            [&it](const auto &move){ return turn_to_relative(move, *it); });
        *it = turn_to_canonical(*it);
    }

    for (const auto &move : moves)
        if (!move.empty())
            ret += move + ' ';

    ret.pop_back();
    return ret;
}
*/
