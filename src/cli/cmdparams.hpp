#pragma once
#include <string>

// Get a line from stdin.
std::istream& getl(std::string& line);

// Draw ">" pointer in the shell.
void point();

// Parses the argument strings provided by the command line.
int parse(const int argc, const char *argv[]);
