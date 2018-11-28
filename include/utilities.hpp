#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include <iostream>
#include <string>

#ifdef NDEBUG
    #define LOG(x)
#else
    #define LOG(x) std::cout << (x) << std::endl;
#endif

auto random_scramble(std::size_t length = 20)    -> std::string;
auto inverse_algorithm(const std::string &alg)   -> std::string;
//auto canonical_algorithm(const std::string &alg) -> std::string;

#endif
