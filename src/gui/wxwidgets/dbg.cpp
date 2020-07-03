#include "../../cpu/interpreter/err.hpp"
#include "../../cpu/interpreter/interp.hpp"
#include <algorithm>
#include <list>

namespace {
	std::list<memory_address> bp; // Breakpoints set by the user.

    // Check if program counter did hit a breakpoint.
    bool hit_bp() { 
        return std::find(std::begin(bp), std::end(bp), Cpu::pc) != std::end(bp); 
    }
}

namespace Dbg {
    // Check if any breakpoints is set.
    bool has_user_set_any_breakpoints() {
        return bp.empty();
    }

    // Step a single instruction and check if a breakpoint is hit.
    bool breakstep() {
        if (bp.empty())
            throw err("No breakpoints set!");
    	Interpreter::step();
    	return hit_bp();
    }

    // Set a breakpoint at a given virtual address.
    void bpset(const memory_address addr) {
        bp.push_back(addr); 
    }

    // Remove a breakpoint at a given virtual address.
    void bprm(const memory_address addr) {
        bp.remove(addr); 
    }

    bool isbp(const memory_address addr) {
        return std::find(std::begin(bp), std::end(bp), addr) != std::end(bp); 
    }
}
