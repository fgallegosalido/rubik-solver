#include <algorithm>
#include <array>
#include <random>
#include <sstream>
#include <string>
#include <cctype>

std::string random_scramble(std::size_t length){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<unsigned> dis(0, 5);

    std::string scramble;

    constexpr const char *moves[] = {"U", "F", "R", "B", "L", "D"};
    constexpr const char *dirs[] = {"", "'", "2"};

    for (std::size_t i=0; i<length; ++i){
        scramble += moves[dis(gen)];
        scramble += dirs[dis(gen)%3];
        scramble += " ";
    }

    return scramble;
}

std::string inverse_algorithm(const std::string &alg){
    using namespace std::string_literals;

    std::string alg_copy(alg.size(), ' ');
    std::reverse_copy(alg.begin(), alg.end(), alg_copy.begin());

    std::stringstream ss(alg_copy);
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

    return ret;
}

std::size_t turn_count(const std::string &alg){
    std::stringstream ss(alg);
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


/*const color& read_position(const std::string& pos) const{
    if      (pos == UFL) return UFL();
    else if (pos == FLU) return FLU();
    else if (pos == LUF) return LUF();
    else if (pos == FLU) return FLU();
    else if (pos == LUF) return LUF();
}*/

/* WIP: Translate any algorithm to canonical moves (U, R, F, D, L, B)
void Cube::turn_to_canonical(std::string& t)
{
   auto aux = std::tolower(t[0]);

   if (aux == 'm' || aux == 'x' || aux == 'r' || aux == 'l'){
      for (auto i : parity){
         if (i.first == xy){

         }
         else if (i.first == xz){

         }
      }
   }
   else if (aux == 'e' || aux == 'y' || aux == 'u' || aux == 'd'){
      for (auto i : parity){
         if (i.first == xy){

         }
         else if (i.first == yz){

         }
      }
   }
   else if (aux == 's' || aux == 'z' || aux == 'f' || aux == 'b'){
      for (auto i : parity){
         if (i.first == yz){

         }
         else if (i.first == xz){

         }
      }
   }
   else{
      t = "";
   }
}

std::string Cube::algorithm_to_canonical(const std::string& alg){
   std::stringstream ss(alg);
   std::string ret;
   std::string turn;

   std::vector<std::pair<plane, direction>> parity;

   while (ss >> turn){
      if (turn == "M" || turn == "r'" || turn == "l" || turn == "x'"){
         parity.emplace_back(yz, clock_wise);
      }
      else if (turn == "M'" || turn == "r" || turn == "l'" || turn == "x"){
         parity.emplace_back(yz, anti_clock_wise);
      }
      else if (turn == "M2" || turn == "r2" || turn == "l2" || turn == "x2"){
         parity.emplace_back(yz, two_turns);
      }
      else if (turn == "E" || turn == "u'" || turn == "d" || turn == "y'"){
         parity.emplace_back(xz, clock_wise);
      }
      else if (turn == "E'" || turn == "u" || turn == "d'" || turn == "y"){
         parity.emplace_back(xz, anti_clock_wise);
      }
      else if (turn == "E2" || turn == "u2" || turn == "d2" || turn == "y2"){
         parity.emplace_back(xz, two_turns);
      }
      else if (turn == "S" || turn == "f" || turn == "b'" || turn == "z"){
         parity.emplace_back(xy, clock_wise);
      }
      else if (turn == "S'" || turn == "f'" || turn == "b" || turn == "z'"){
         parity.emplace_back(xy, anti_clock_wise);
      }
      else if (turn == "S2" || turn == "f2" || turn == "b2" || turn == "z2"){
         parity.emplace_back(xy, two_turns);
      }

      ret += turn_to_canonical(turn, parity);
   }

   return ret;
}
*/
