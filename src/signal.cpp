#include <csignal>
#include <cstdlib>
#include "cpu/interpreter/err.hpp"

static void handler(int no) {
    switch (no) {
    case SIGINT: // User pressed CTRL+C.
        exit(1);
    }
}

void register_signals() {
    if (signal(SIGINT, handler) == SIG_ERR)
        throw err("Cannot register SIGINT signal-handler!");
}
