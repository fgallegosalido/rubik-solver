#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "storage.hpp"

enum color {white, green, red, blue, magenta, yellow};
enum direction {clock_wise, anti_clock_wise, two_turns};
enum plane {xy, yz, xz};

class Cube{
   public:
      // Canonical turns
      void U();
      void Uu();
      void U2();

      void F();
      void Ff();
      void F2();

      void R();
      void Rr();
      void R2();

      void D();
      void Dd();
      void D2();

      void B();
      void Bb();
      void B2();

      void L();
      void Ll();
      void L2();


      // Center layer turns
      void M();
      void Mm();
      void M2();

      void E();
      void Ee();
      void E2();

      void S();
      void Ss();
      void S2();

      // Fat canonical turns
      void u();
      void uu();
      void u2();

      void f();
      void ff();
      void f2();

      void r();
      void rr();
      void r2();

      void d();
      void dd();
      void d2();

      void b();
      void bb();
      void b2();

      void l();
      void ll();
      void l2();


      // Cube rotations
      void x();
      void xx();
      void x2();

      void y();
      void yy();
      void y2();

      void z();
      void zz();
      void z2();

      bool is_solved() const;
      void read_algorithm(const std::string& alg);
      std::string algorithm_to_canonical(const std::string& alg);

      friend std::ostream& operator<<(std::ostream& out, Cube& o);

   private:
      storage<color> cube{
         white, white, white, white, white, white, white, white, white,
         green, green, green, green, green, green, green, green, green,
         red, red, red, red, red, red, red, red, red,
         blue, blue, blue, blue, blue, blue, blue, blue, blue,
         magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta, magenta,
         yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow
      };

      std::string square_string(color c);
      template<typename T, typename ...Args>
      std::string square_string(T c, Args ...rest);

      void turn_face(storage<color>::size_type face, direction dir);
      void read_turn(const std::string& t);
      void turn_to_canonical(std::string& t,
                                    const std::vector<std::pair<plane, direction>>& parity);
};
