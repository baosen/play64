#include "interp.hpp"
#include "normals/normals.hpp"
#include "../tlb/tlb.hpp"
#include "../../memory_map/physical_memory/mi/mi.hpp"
#include "err.hpp"

// Interprets MIPS III instructions.
namespace Interpreter {
// The Nintendo 64 consist of a CPU executing instructions from the MIPS III instruction set, a MIPS COP0 control unit and a COP1 floating-point co-processor.
// It has no COP2 and COP3 processors.

    // Fetch an instruction from the memory.
    Instr fetch() { 
        return Instr(Vmem::rd32(Cpu::pc)); 
    }

    // Execute an instruction given.
    void execute_instruction(const Instr instruction) {
    	// Check if is a NOP (no operation)-instruction.
    	if (instruction.is_nop())
            goto decrement_random;

    	// Interpret NORMAL-instruction.
    	Normals::call(instruction);

    decrement_random:
        // Decrements the control unit's random register, which is decremented each time an instruction is executed (p.69 VR4300).
        System_control::decrement_random();
    }

    // Execute exactly one single MIPS-instruction fetched from RD-ram memory.
    void step() {
start:
    	try {
            // Fetch new instruction.
            const auto new_instruction_fetched = fetch();

            // Advance program counter.
            Cpu::advance_program_counter();

            // Execute instruction.
            execute_instruction(new_instruction_fetched);

            // Check for pending interrupts and execute them.
            Mi::intif();
        } catch (const Tlb::Miss& m){
            // HACK: Execute through the TLB miss handler.
            goto start;
        } catch (const Dbgerr& e) {
            throw;
        } catch (...) {
    		Cpu::revert();
            throw;
        }
    }

    // Reset system.
    void reset() {
        // Reset CPU registers.
        Cpu::reset();

        // Reset the control coprocessor (Coprocessor 0).
        System_control::reset();

        // Reset Translation Look-Aside Buffer.
        Tlb::reset();
    }
}
// Actually, the CPU begins to execute the code stored at address 0xbfc0 0000 known as the PIF Boot ROM. 
// It is assumed it does some security checks (Twice CRC checks, compute seed...) before loading the game code stored in the cartridge into the system's RDram.
// My emulator skips executing this code. Instead, it sets the values that is computed by the PIF Boot ROM code so the game running executes without failing a security check.
