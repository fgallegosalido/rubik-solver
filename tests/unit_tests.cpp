#include <iostream>
#include "cube.hpp"

// Boost's Unit Test Framework
#define BOOST_TEST_MODULE Turns Test
#include <boost/test/included/unit_test.hpp>

static constexpr const char* test_scrambles[][2] = {
   {"L' F2 R B2 D2 L' B2 U B2 L B' R' U B2 D' R U B'",
    "L2 U2 L F' U' F2 U D' B' R2 F2 D B2 D' U F D F' U' F"},
   {"R' U' F R2 D' B2 F2 R2 D' U2 F2 U' L2 B D2 B' L' B' L2 D' U L2 B' U2 R' U' F",
    "L B' L D' L' D2 L D L' D' B D2 R D' R2 D' F2 B2 R F' D R2"}
};

Cube test_cube;

BOOST_AUTO_TEST_CASE(first_test){
   test_cube.read_algorithm(test_scrambles[0][0]);
   test_cube.read_algorithm(test_scrambles[0][1]);
   BOOST_TEST(test_cube.is_solved());

   test_cube.read_algorithm(test_scrambles[1][0]);
   test_cube.read_algorithm(test_scrambles[1][1]);
   BOOST_TEST(test_cube.is_solved());
}
