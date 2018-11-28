#ifndef _METHOD_HPP_
#define _METHOD_HPP_

#include <memory>
#include "cube.hpp"

class Method{
protected:
    Cube &cube_ref;

public:
    explicit Method(Cube &ref) : cube_ref{ref}{};
    virtual void apply_method() = 0;

};

#endif
