#ifndef _METHOD_HPP_
#define _METHOD_HPP_

#include <string>
#include "cube.hpp"

// This abstract class lets you implement a method.
// The method doesn't need to solve the cube, but partially solve it
class Method{
protected:
    Cube &cube_ref;
    const std::string &method_name;

public:
    explicit Method(Cube &ref, const std::string &name = "Default method name")
        : cube_ref{ref}, method_name{name}{}

    virtual bool method_finished() = 0;
    virtual std::string apply_method() = 0;
};

#endif
