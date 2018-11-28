#include <iostream>

#include "cube.hpp"
#include "old_pochmann_corners.hpp"
#include "old_pochmann_edges.hpp"
#include "utilities.hpp"

int main(){
    Cube c;
    c.read_algorithm(random_scramble());

    std::cout << "Cubo con mezcla aleatoria:\n\n" << c << "\n" << std::endl;

    OldPochmannCorners corners{c};
    OldPochmannEdges edges{c};

    std::cout << "Resolviendo el cubo..." << std::endl;

    corners.apply_method();
    edges.apply_method();

    std::cout << "\nCubo resuelto:\n\n" << c << std::endl;
}
