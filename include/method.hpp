#ifndef _METHOD_HPP_
#define _METHOD_HPP_

#include <string>
#include <utility>
#include "cube.hpp"

// This abstract class lets you implement a method.
// The method doesn't need to solve the cube, but partially solve it
class Method{
protected:
    Cube &cube_ref;                 // A reference to the cube being solved
    const std::string method_name; // The method name

public:
    explicit Method(Cube &ref, std::string name_ = "Default method name")
        : cube_ref{ref}, method_name{std::move(name_)}{}

    // A method shouldn't be copied, so we delete those destructors
    Method(const Method&)            = delete;
    Method(Method&&)                 = delete;
    Method& operator=(const Method&) = delete;
    Method& operator=(Method&&)      = delete;

    virtual ~Method()                = default;

    const std::string& name() const{
        return method_name;
    }

    // Every method must implement a function to check if the method is applied
    // and a function to apply the method
    virtual bool method_finished() const = 0;
    virtual std::string apply_method() = 0;
};

#endif
