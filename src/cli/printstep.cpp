#include <iostream>
#include "../cpu/interpreter/interp.hpp"
#include "../disassembler/decode.hpp"
#include "../cpu/interpreter/err.hpp"
using namespace std;

// Single-step.
void printstep() {
    try {
        // Print out current instruction.
        cout << hex << Cpu::pc << ": " << decode(Vmem::rd32(Cpu::pc)) << endl;
        // Execute current instruction.
        Interpreter::step();
    } catch (const err& e) {
        cout << e.what() << endl;
        throw;
    }
}
