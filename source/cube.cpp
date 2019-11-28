#include "cube.hpp"

#include <algorithm>
#include <utility>

#include "cube_storage.hpp"
#include "utilities.hpp"

Cube::Cube(std::size_t length)
    : Cube{random_scramble(length)} {}

// This function turns the 9 squares of a face in a certain direction
void Cube::turn_face(cube_size_type face, direction dir){
    switch (dir) {
        case clock_wise:
            get(face, 0) =  std::exchange(get(face, 6),
                            std::exchange(get(face, 8),
                            std::exchange(get(face, 2),
                            get(face, 0))));
            get(face, 1) =  std::exchange(get(face, 3),
                            std::exchange(get(face, 7),
                            std::exchange(get(face, 5),
                            get(face, 1))));
            break;
        case anti_clock_wise:
            get(face, 0) =  std::exchange(get(face, 2),
                            std::exchange(get(face, 8),
                            std::exchange(get(face, 6),
                            get(face, 0))));
            get(face, 1) =  std::exchange(get(face, 5),
                            std::exchange(get(face, 7),
                            std::exchange(get(face, 3),
                            get(face, 1))));
            break;
        case two_turns:
            std::swap(get(face, 0), get(face, 8));
            std::swap(get(face, 1), get(face, 7));
            std::swap(get(face, 2), get(face, 6));
            std::swap(get(face, 3), get(face, 5));
            break;
     }
}

// Canonical turns
// These turns must be hard-coded
// It looks like so much repetition, but it's not,
// so that's what have to be done
void Cube::U(){
    // Exchange upper face squares
    turn_face(UP, clock_wise);

    auto tmp = get(FRONT, 0);
    get(FRONT, 0) = get(RIGHT, 0);
    get(RIGHT, 0) = get(BACK, 0);
    get(BACK, 0) = get(LEFT, 0);
    get(LEFT, 0) = tmp;

    tmp = get(FRONT, 1);
    get(FRONT, 1) = get(RIGHT, 1);
    get(RIGHT, 1) = get(BACK, 1);
    get(BACK, 1) = get(LEFT, 1);
    get(LEFT, 1) = tmp;

    tmp = get(FRONT, 2);
    get(FRONT, 2) = get(RIGHT, 2);
    get(RIGHT, 2) = get(BACK, 2);
    get(BACK, 2) = get(LEFT, 2);
    get(LEFT, 2) = tmp;
}
void Cube::Uu(){
    // Exchange upper face squares
    turn_face(UP, anti_clock_wise);

    auto tmp = get(FRONT, 0);
    get(FRONT, 0) = get(LEFT, 0);
    get(LEFT, 0) = get(BACK, 0);
    get(BACK, 0) = get(RIGHT, 0);
    get(RIGHT, 0) = tmp;

    tmp = get(FRONT, 1);
    get(FRONT, 1) = get(LEFT, 1);
    get(LEFT, 1) = get(BACK, 1);
    get(BACK, 1) = get(RIGHT, 1);
    get(RIGHT, 1) = tmp;

    tmp = get(FRONT, 2);
    get(FRONT, 2) = get(LEFT, 2);
    get(LEFT, 2) = get(BACK, 2);
    get(BACK, 2) = get(RIGHT, 2);
    get(RIGHT, 2) = tmp;
}
void Cube::U2(){
    // Exchange upper face squares
    turn_face(UP, two_turns);

    std::swap(get(FRONT, 0), get(BACK, 0));
    std::swap(get(FRONT, 1), get(BACK, 1));
    std::swap(get(FRONT, 2), get(BACK, 2));
    std::swap(get(RIGHT, 0), get(LEFT, 0));
    std::swap(get(RIGHT, 1), get(LEFT, 1));
    std::swap(get(RIGHT, 2), get(LEFT, 2));
}

void Cube::F(){
    // Exchange front face squares
    turn_face(FRONT, clock_wise);

    auto tmp = get(UP, 6);
    get(UP, 6) = get(LEFT, 8);
    get(LEFT, 8) = get(DOWN, 2);
    get(DOWN, 2) = get(RIGHT, 0);
    get(RIGHT, 0) = tmp;

    tmp = get(UP, 7);
    get(UP, 7) = get(LEFT, 5);
    get(LEFT, 5) = get(DOWN, 1);
    get(DOWN, 1) = get(RIGHT, 3);
    get(RIGHT, 3) = tmp;

    tmp = get(UP, 8);
    get(UP, 8) = get(LEFT, 2);
    get(LEFT, 2) = get(DOWN, 0);
    get(DOWN, 0) = get(RIGHT, 6);
    get(RIGHT, 6) = tmp;
}
void Cube::Ff(){
    // Exchange front face squares
    turn_face(FRONT, anti_clock_wise);

    auto tmp = get(UP, 6);
    get(UP, 6) = get(RIGHT, 0);
    get(RIGHT, 0) = get(DOWN, 2);
    get(DOWN, 2) = get(LEFT, 8);
    get(LEFT, 8) = tmp;

    tmp = get(UP, 7);
    get(UP, 7) = get(RIGHT, 3);
    get(RIGHT, 3) = get(DOWN, 1);
    get(DOWN, 1) = get(LEFT, 5);
    get(LEFT, 5) = tmp;

    tmp = get(UP, 8);
    get(UP, 8) = get(RIGHT, 6);
    get(RIGHT, 6) = get(DOWN, 0);
    get(DOWN, 0) = get(LEFT, 2);
    get(LEFT, 2) = tmp;
}
void Cube::F2(){
    // Exchange front face squares
    turn_face(FRONT, two_turns);

    std::swap(get(UP, 6), get(DOWN, 2));
    std::swap(get(UP, 7), get(DOWN, 1));
    std::swap(get(UP, 8), get(DOWN, 0));
    std::swap(get(RIGHT, 0), get(LEFT, 8));
    std::swap(get(RIGHT, 3), get(LEFT, 5));
    std::swap(get(RIGHT, 6), get(LEFT, 2));
}

void Cube::R(){
    // Exchange upper face squares
    turn_face(RIGHT, clock_wise);

    auto tmp = get(UP, 2);
    get(UP, 2) = get(FRONT, 2);
    get(FRONT, 2) = get(DOWN, 2);
    get(DOWN, 2) = get(BACK, 6);
    get(BACK, 6) = tmp;

    tmp = get(UP, 5);
    get(UP, 5) = get(FRONT, 5);
    get(FRONT, 5) = get(DOWN, 5);
    get(DOWN, 5) = get(BACK, 3);
    get(BACK, 3) = tmp;

    tmp = get(UP, 8);
    get(UP, 8) = get(FRONT, 8);
    get(FRONT, 8) = get(DOWN, 8);
    get(DOWN, 8) = get(BACK, 0);
    get(BACK, 0) = tmp;
}
void Cube::Rr(){
    // Exchange upper face squares
    turn_face(RIGHT, anti_clock_wise);

    auto tmp = get(UP, 2);
    get(UP, 2) = get(BACK, 6);
    get(BACK, 6) = get(DOWN, 2);
    get(DOWN, 2) = get(FRONT, 2);
    get(FRONT, 2) = tmp;

    tmp = get(UP, 5);
    get(UP, 5) = get(BACK, 3);
    get(BACK, 3) = get(DOWN, 5);
    get(DOWN, 5) = get(FRONT, 5);
    get(FRONT, 5) = tmp;

    tmp = get(UP, 8);
    get(UP, 8) = get(BACK, 0);
    get(BACK, 0) = get(DOWN, 8);
    get(DOWN, 8) = get(FRONT, 8);
    get(FRONT, 8) = tmp;
}
void Cube::R2(){
    // Exchange upper face squares
    turn_face(RIGHT, two_turns);

    std::swap(get(UP, 2), get(DOWN, 2));
    std::swap(get(UP, 5), get(DOWN, 5));
    std::swap(get(UP, 8), get(DOWN, 8));
    std::swap(get(FRONT, 2), get(BACK, 6));
    std::swap(get(FRONT, 5), get(BACK, 3));
    std::swap(get(FRONT, 8), get(BACK, 0));
}

void Cube::D(){
    // Exchange upper face squares
    turn_face(DOWN, clock_wise);

    auto tmp = get(FRONT, 6);
    get(FRONT, 6) = get(LEFT, 6);
    get(LEFT, 6) = get(BACK, 6);
    get(BACK, 6) = get(RIGHT, 6);
    get(RIGHT, 6) = tmp;

    tmp = get(FRONT, 7);
    get(FRONT, 7) = get(LEFT, 7);
    get(LEFT, 7) = get(BACK, 7);
    get(BACK, 7) = get(RIGHT, 7);
    get(RIGHT, 7) = tmp;

    tmp = get(FRONT, 8);
    get(FRONT, 8) = get(LEFT, 8);
    get(LEFT, 8) = get(BACK, 8);
    get(BACK, 8) = get(RIGHT, 8);
    get(RIGHT, 8) = tmp;
}
void Cube::Dd(){
    // Exchange upper face squares
    turn_face(DOWN, anti_clock_wise);

    auto tmp = get(FRONT, 6);
    get(FRONT, 6) = get(RIGHT, 6);
    get(RIGHT, 6) = get(BACK, 6);
    get(BACK, 6) = get(LEFT, 6);
    get(LEFT, 6) = tmp;

    tmp = get(FRONT, 7);
    get(FRONT, 7) = get(RIGHT, 7);
    get(RIGHT, 7) = get(BACK, 7);
    get(BACK, 7) = get(LEFT, 7);
    get(LEFT, 7) = tmp;

    tmp = get(FRONT, 8);
    get(FRONT, 8) = get(RIGHT, 8);
    get(RIGHT, 8) = get(BACK, 8);
    get(BACK, 8) = get(LEFT, 8);
    get(LEFT, 8) = tmp;
}
void Cube::D2(){
    // Exchange upper face squares
    turn_face(DOWN, two_turns);

    std::swap(get(FRONT, 6), get(BACK, 6));
    std::swap(get(FRONT, 7), get(BACK, 7));
    std::swap(get(FRONT, 8), get(BACK, 8));
    std::swap(get(RIGHT, 6), get(LEFT, 6));
    std::swap(get(RIGHT, 7), get(LEFT, 7));
    std::swap(get(RIGHT, 8), get(LEFT, 8));
}

void Cube::B(){
    // Exchange upper face squares
    turn_face(BACK, clock_wise);

    auto tmp = get(UP, 0);
    get(UP, 0) = get(RIGHT, 2);
    get(RIGHT, 2) = get(DOWN, 8);
    get(DOWN, 8) = get(LEFT, 6);
    get(LEFT, 6) = tmp;

    tmp = get(UP, 1);
    get(UP, 1) = get(RIGHT, 5);
    get(RIGHT, 5) = get(DOWN, 7);
    get(DOWN, 7) = get(LEFT, 3);
    get(LEFT, 3) = tmp;

    tmp = get(UP, 2);
    get(UP, 2) = get(RIGHT, 8);
    get(RIGHT, 8) = get(DOWN, 6);
    get(DOWN, 6) = get(LEFT, 0);
    get(LEFT, 0) = tmp;
}
void Cube::Bb(){
    // Exchange upper face squares
    turn_face(BACK, anti_clock_wise);

    auto tmp = get(UP, 0);
    get(UP, 0) = get(LEFT, 6);
    get(LEFT, 6) = get(DOWN, 8);
    get(DOWN, 8) = get(RIGHT, 2);
    get(RIGHT, 2) = tmp;

    tmp = get(UP, 1);
    get(UP, 1) = get(LEFT, 3);
    get(LEFT, 3) = get(DOWN, 7);
    get(DOWN, 7) = get(RIGHT, 5);
    get(RIGHT, 5) = tmp;

    tmp = get(UP, 2);
    get(UP, 2) = get(LEFT, 0);
    get(LEFT, 0) = get(DOWN, 6);
    get(DOWN, 6) = get(RIGHT, 8);
    get(RIGHT, 8) = tmp;
}
void Cube::B2(){
    // Exchange upper face squares
    turn_face(BACK, two_turns);

    std::swap(get(UP, 0), get(DOWN, 8));
    std::swap(get(UP, 1), get(DOWN, 7));
    std::swap(get(UP, 2), get(DOWN, 6));
    std::swap(get(RIGHT, 2), get(LEFT, 6));
    std::swap(get(RIGHT, 5), get(LEFT, 3));
    std::swap(get(RIGHT, 8), get(LEFT, 0));
}

void Cube::L(){
    // Exchange upper face squares
    turn_face(LEFT, clock_wise);

    auto tmp = get(UP, 0);
    get(UP, 0) = get(BACK, 8);
    get(BACK, 8) = get(DOWN, 0);
    get(DOWN, 0) = get(FRONT, 0);
    get(FRONT, 0) = tmp;

    tmp = get(UP, 3);
    get(UP, 3) = get(BACK, 5);
    get(BACK, 5) = get(DOWN, 3);
    get(DOWN, 3) = get(FRONT, 3);
    get(FRONT, 3) = tmp;

    tmp = get(UP, 6);
    get(UP, 6) = get(BACK, 2);
    get(BACK, 2) = get(DOWN, 6);
    get(DOWN, 6) = get(FRONT, 6);
    get(FRONT, 6) = tmp;
}
void Cube::Ll(){
    // Exchange upper face squares
    turn_face(LEFT, anti_clock_wise);

    auto tmp = get(UP, 0);
    get(UP, 0) = get(FRONT, 0);
    get(FRONT, 0) = get(DOWN, 0);
    get(DOWN, 0) = get(BACK, 8);
    get(BACK, 8) = tmp;

    tmp = get(UP, 3);
    get(UP, 3) = get(FRONT, 3);
    get(FRONT, 3) = get(DOWN, 3);
    get(DOWN, 3) = get(BACK, 5);
    get(BACK, 5) = tmp;

    tmp = get(UP, 6);
    get(UP, 6) = get(FRONT, 6);
    get(FRONT, 6) = get(DOWN, 6);
    get(DOWN, 6) = get(BACK, 2);
    get(BACK, 2) = tmp;
}
void Cube::L2(){
    // Exchange upper face squares
    turn_face(LEFT, two_turns);

    std::swap(get(UP, 0), get(DOWN, 0));
    std::swap(get(UP, 3), get(DOWN, 3));
    std::swap(get(UP, 6), get(DOWN, 6));
    std::swap(get(FRONT, 0), get(BACK, 8));
    std::swap(get(FRONT, 3), get(BACK, 5));
    std::swap(get(FRONT, 6), get(BACK, 2));
}

// Center layer turns
// These ones also have to be hard-coded
void Cube::M(){
    auto tmp = get(UP, 1);
    get(UP, 1) = get(BACK, 7);
    get(BACK, 7) = get(DOWN, 1);
    get(DOWN, 1) = get(FRONT, 1);
    get(FRONT, 1) = tmp;

    tmp = get(UP, 4);
    get(UP, 4) = get(BACK, 4);
    get(BACK, 4) = get(DOWN, 4);
    get(DOWN, 4) = get(FRONT, 4);
    get(FRONT, 4) = tmp;

    tmp = get(UP, 7);
    get(UP, 7) = get(BACK, 1);
    get(BACK, 1) = get(DOWN, 7);
    get(DOWN, 7) = get(FRONT, 7);
    get(FRONT, 7) = tmp;
}
void Cube::Mm(){
    auto tmp = get(UP, 1);
    get(UP, 1) = get(FRONT, 1);
    get(FRONT, 1) = get(DOWN, 1);
    get(DOWN, 1) = get(BACK, 7);
    get(BACK, 7) = tmp;

    tmp = get(UP, 4);
    get(UP, 4) = get(FRONT, 4);
    get(FRONT, 4) = get(DOWN, 4);
    get(DOWN, 4) = get(BACK, 4);
    get(BACK, 4) = tmp;

    tmp = get(UP, 7);
    get(UP, 7) = get(FRONT, 7);
    get(FRONT, 7) = get(DOWN, 7);
    get(DOWN, 7) = get(BACK, 1);
    get(BACK, 1) = tmp;
}
void Cube::M2(){
    std::swap(get(UP, 1), get(DOWN, 1));
    std::swap(get(UP, 4), get(DOWN, 4));
    std::swap(get(UP, 7), get(DOWN, 7));
    std::swap(get(FRONT, 1), get(BACK, 7));
    std::swap(get(FRONT, 4), get(BACK, 4));
    std::swap(get(FRONT, 7), get(BACK, 1));
}

void Cube::E(){
    auto tmp = get(FRONT, 3);
    get(FRONT, 3) = get(LEFT, 3);
    get(LEFT, 3) = get(BACK, 3);
    get(BACK, 3) = get(RIGHT, 3);
    get(RIGHT, 3) = tmp;

    tmp = get(FRONT, 4);
    get(FRONT, 4) = get(LEFT, 4);
    get(LEFT, 4) = get(BACK, 4);
    get(BACK, 4) = get(RIGHT, 4);
    get(RIGHT, 4) = tmp;

    tmp = get(FRONT, 5);
    get(FRONT, 5) = get(LEFT, 5);
    get(LEFT, 5) = get(BACK, 5);
    get(BACK, 5) = get(RIGHT, 5);
    get(RIGHT, 5) = tmp;
}
void Cube::Ee(){
    auto tmp = get(FRONT, 3);
    get(FRONT, 3) = get(RIGHT, 3);
    get(RIGHT, 3) = get(BACK, 3);
    get(BACK, 3) = get(LEFT, 3);
    get(LEFT, 3) = tmp;

    tmp = get(FRONT, 4);
    get(FRONT, 4) = get(RIGHT, 4);
    get(RIGHT, 4) = get(BACK, 4);
    get(BACK, 4) = get(LEFT, 4);
    get(LEFT, 4) = tmp;

    tmp = get(FRONT, 5);
    get(FRONT, 5) = get(RIGHT, 5);
    get(RIGHT, 5) = get(BACK, 5);
    get(BACK, 5) = get(LEFT, 5);
    get(LEFT, 5) = tmp;
}
void Cube::E2(){
    std::swap(get(FRONT, 3), get(BACK, 3));
    std::swap(get(FRONT, 4), get(BACK, 4));
    std::swap(get(FRONT, 5), get(BACK, 5));
    std::swap(get(RIGHT, 3), get(LEFT, 3));
    std::swap(get(RIGHT, 4), get(LEFT, 4));
    std::swap(get(RIGHT, 5), get(LEFT, 5));
}

void Cube::S(){
    auto tmp = get(RIGHT, 1);
    get(RIGHT, 1) = get(UP, 3);
    get(UP, 3) = get(LEFT, 7);
    get(LEFT, 7) = get(DOWN, 5);
    get(DOWN, 5) = tmp;

    tmp = get(RIGHT, 4);
    get(RIGHT, 4) = get(UP, 4);
    get(UP, 4) = get(LEFT, 4);
    get(LEFT, 4) = get(DOWN, 4);
    get(DOWN, 4) = tmp;

    tmp = get(RIGHT, 7);
    get(RIGHT, 7) = get(UP, 5);
    get(UP, 5) = get(LEFT, 1);
    get(LEFT, 1) = get(DOWN, 3);
    get(DOWN, 3) = tmp;
}
void Cube::Ss(){
    auto tmp = get(RIGHT, 1);
    get(RIGHT, 1) = get(DOWN, 5);
    get(DOWN, 5) = get(LEFT, 7);
    get(LEFT, 7) = get(UP, 3);
    get(UP, 3) = tmp;

    tmp = get(RIGHT, 4);
    get(RIGHT, 4) = get(DOWN, 4);
    get(DOWN, 4) = get(LEFT, 4);
    get(LEFT, 4) = get(UP, 4);
    get(UP, 4) = tmp;

    tmp = get(RIGHT, 7);
    get(RIGHT, 7) = get(DOWN, 3);
    get(DOWN, 3) = get(LEFT, 1);
    get(LEFT, 1) = get(UP, 5);
    get(UP, 5) = tmp;
}
void Cube::S2(){
    std::swap(get(RIGHT, 1), get(LEFT, 7));
    std::swap(get(RIGHT, 4), get(LEFT, 4));
    std::swap(get(RIGHT, 7), get(LEFT, 1));
    std::swap(get(DOWN, 5), get(UP, 3));
    std::swap(get(DOWN, 4), get(UP, 4));
    std::swap(get(DOWN, 3), get(UP, 5));
}

// The rest of the turns can be implemented based on the previous ones

// Fat canonical turns
void Cube::u(){ U(); Ee(); }
void Cube::uu(){ Uu(); E(); }
void Cube::u2(){ U2(); E2(); }

void Cube::f(){ F(); S(); }
void Cube::ff(){ Ff(); Ss(); }
void Cube::f2(){ F2(); S2(); }

void Cube::r(){ R(); Mm(); }
void Cube::rr(){ Rr(); M(); }
void Cube::r2(){ R2(); M2(); }

void Cube::d(){ D(); E(); }
void Cube::dd(){ Dd(); Ee(); }
void Cube::d2(){ D2(); E2(); }

void Cube::b(){ B(); Ss(); }
void Cube::bb(){ Bb(); S(); }
void Cube::b2(){ B2(); S2(); }

void Cube::l(){ L(); M(); }
void Cube::ll(){ Ll(); Mm(); }
void Cube::l2(){ L2(); M2(); }

// Cube rotations
void Cube::x(){ R(); Mm(); Ll(); }
void Cube::xx(){ Rr(); M(); L(); }
void Cube::x2(){ R2(); M2(); L2(); }

void Cube::y(){ U(); Ee(); Dd(); }
void Cube::yy(){ Uu(); E(); D(); }
void Cube::y2(){ U2(); E2(); D2(); }

void Cube::z(){ F(); S(); Bb(); }
void Cube::zz(){ Ff(); Ss(); B(); }
void Cube::z2(){ F2(); S2(); B2(); }

bool Cube::is_solved() const{
    return std::all_of(begin(), std::prev(end()),
        [](const auto &face){
            return std::all_of(std::next(face.begin()), face.end(),
                [first = *face.begin()](const auto &tile){
                    return first == tile;
                }
            );
        }
    );
}
