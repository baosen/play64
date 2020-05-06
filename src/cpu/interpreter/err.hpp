#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

// Stops and reverts the program counter of the interpreter.
using err = std::runtime_error;

inline std::ostream& operator<<(std::ostream& o, const err& e) 
{
    o << e.what();
    return o;
}

// Virtual memory addressing error.
class Vmem_err : public err {
public:
    Vmem_err(const std::string& s) // Construct error message.
        : err(s) 
    {}
};

// Thrown to stop the debugger. Does not revert program counter.
class Dbgerr : public err {
public:
    Dbgerr(const std::string& msg) // Construct error message.
        : err(msg) 
    {}
};

#include "../../logging/log.hpp"
