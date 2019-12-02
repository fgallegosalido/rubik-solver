#include <array>
#include <string_view>
using namespace std::literals::string_view_literals;

#include <catch.hpp>

#include "cube.hpp"

static constexpr std::array scrambles = {
   "L' F2 R B2 D2 L' B2 U B2 L B' R' U B2 D' R U B' L2 U2 L F' U' F2 U D' B' R2 F2 D B2 D' U F D F' U' F"sv,
   "R' U' F R2 D' B2 F2 R2 D' U2 F2 U' L2 B D2 B' L' B' L2 D' U L2 B' U2 R' U' F L B' L D' L' D2 L D L' D' B D2 R D' R2 D' F2 B2 R F' D R2"sv
};

TEST_CASE("scramble_test"){
    Cube cube;

    for (const auto &scramble : scrambles){
        cube << scramble;
        REQUIRE(cube.is_solved());
    }
}
