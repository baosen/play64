#include "../signal.hpp"
#include "cmdparams.hpp"
#include "debug.hpp"
#include "../cpu/interpreter/err.hpp"
using namespace std;

// dbg64: A debugger for the Nintendo 64-system.
int main(const int argc, const char* argv[]) {
    // Parse given command-line arguments.
    int i = parse(argc, argv);
    if (i < 0) {
        error("No arguments provided!");
        return EXIT_FAILURE;
    }

    // Register UNIX signal handlers.
    register_signals();

    // Start debugging!
    debug(argv[i]);

    return EXIT_SUCCESS;
}
