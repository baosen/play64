#include "printstep.hpp"
#include "../memory_map/pak.hpp"

// Single-step and print out instruction.
void trace(const char* s) {
    // Load the rom-file from the file path given into the interpreter.
    Pak::load(s);
    for (;;)
        printstep();
}
