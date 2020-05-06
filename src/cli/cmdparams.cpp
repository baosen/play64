#include <iostream>
#include <cstdio>
#include "cstr.hpp"
using namespace std;

#define PARAM(s) streq(argv[i], #s)

namespace {
    // Prints how to use the program.
    void usage() {
        puts("Usage: dbg64 [options] <ROM>");
    }
    
    // Prints the version of the program.
    void ver() {
        puts("dbg64! A debugger for the Nintendo 64-architecture!\n"
             "Version 0.1 Alpha");
    }
}

istream& getl(string& line) {
    return getline(cin, line);
}

// Prints the bracket that points to the place where the user's input is shown.
void point() {
    cout << "> ";
}

// Parses the argument strings provided by the command line.
// Returns the index of the token.
int parse(const int argc, const char *argv[]) {
    if (argc <= 1)
        return -1;
    int arg = -1;
    for (int i = 0; i < argc; ++i) {
        if (PARAM(-h) || PARAM(--help))
            usage();
        else if (PARAM(-v) || PARAM(--version))
            ver();
        else
            arg = i;
    }
    return arg;
}
