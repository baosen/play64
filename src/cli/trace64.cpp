#include "../signal.hpp"
#include "cmdparams.hpp"
#include "../cpu/interpreter/err.hpp"
#include "trace.hpp"

// trace64: execute ROM and print each executed instruction.
int main(const int argc, const char* argv[]) {
    // Parse given command-line arguments.
    int i = parse(argc, argv);
    if (i < 0) {
        error("No arguments provided!");
        return EXIT_FAILURE;
    }
    // Register UNIX signal handlers.
    register_signals();
    // Start tracing!
    trace(argv[i]);
    return 0;
}
