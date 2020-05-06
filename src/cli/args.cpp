#include <iostream>
#include "args.hpp"
#include "../cpu/interpreter/err.hpp"
using namespace std;

const char* parse_args(const int argc, const char **argv) {
    for (int i = 1; i < argc; i++) {
        const auto c = &argv[i][0];
        if (*c == '-')
            continue;
        return c;
    }
    return nullptr;
}

static void usage() {
    cout << "Usage: play64 [options] <ROM>" << endl;
}

// Check for any passed input arguments:
void check_count(const int argc) {
    if (argc <= 1) {
        error("No arguments!");
        usage();
        exit(EXIT_FAILURE);
    }
}
