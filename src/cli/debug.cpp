#include "../memory_map/pak.hpp"
#include "../cpu/interpreter/interp.hpp"
#include "cmdparams.hpp"
#include "../cpu/interpreter/err.hpp"
#include "printstep.hpp"
using namespace std;

#define CMD(s1, s2) line == #s1 || line == #s2

namespace {
    // Run the game!
    void run() {
        for (;;) {
            //Interpreter::step();
            printstep();
        }
    }

    void cls() {
        if (system("clear") == -1)
            puts("Failed clearing shell.");
    }
}

void debug(const char *s) {
    // Load the rom-file from the file path given into the interpreter.
    Pak::load(s);
    
    // Show debug cmd interface.
    point();
    string line, old("dummy"); // TODO: Simplify.
    while (getl(line)) {
        try {
retry:
            if (CMD(r, run))
                run();
            else if (CMD(s, step))
                printstep();
            else if (CMD(b, break))
                puts("TODO: Implement break at address.");
            else if (CMD(bs, breakstep))
                ;
                //breakstep();
            else if (CMD(e, exit))
                return;
            else if (CMD(q, quit))
                return;
            else if (CMD( ,\n)) {
                line = old;
                goto retry;
            } else if (CMD(p, print))
                ;
                //printpc();
            else if (CMD(cls, clear)) {
                cls();
            } else
                puts("I don't understand your command.");
            old = line;
        } catch (const Vmem_err& e) {
            error(e.what());
            printf("pc: %x\n", Cpu::pc);
        } catch (const err& e) {
            error(e.what());
            printf("pc: %x\n", Cpu::pc);
        }
        point();
    }
}
