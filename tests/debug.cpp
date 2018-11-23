#include <iostream>
#include "cube.hpp"

int main(){
   Cube c;
   std::string t;

   while(true){
      std::cout << "Type a valid sequence of turns --> ";
      std::getline(std::cin, t);

      c.read_algorithm(t);
      std::cout << c << std::endl;
   }
}
