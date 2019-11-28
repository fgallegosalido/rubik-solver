#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include <iostream>
#include <string>

// Returns a new scramble as a string
auto random_scramble(std::size_t length = 20)       -> std::string;
// Returns a correct algorithm (deleting invalid input)
auto parse_algorithm(const std::string &alg)        -> std::string;
// Returns the inverse of an algorithm as a string
auto inverse_algorithm(const std::string &alg)      -> std::string;
// Returns the same algorithm, but cancelling moves
auto cancel_moves(const std::string &alg)           -> std::string;
// Returns the number of turns in an algorithm
auto turn_count(const std::string &alg)             -> std::size_t;
// Check if two moves are from opposite faces
// WIP: Returns an algorithm using only the canonical moves (U, F, R, B, L, D)
//auto algorithm_to_canonical(const std::string &alg) -> std::string;

#endif
