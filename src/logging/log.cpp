#include "../cpu/interpreter/err.hpp"

// Print error code and exit.
void die(const int code) 
{
    std::cerr << "\033[1;31m" << "Error code: " << std::hex << code << "\033[0m" << std::endl;
    exit(code);
}

// Print info log message.
void log(const std::string& s)
{
    std::cerr << "\033[1;37mInformation:\033[0m " << s << std::endl;
}

// Print info log message.
void log(const char* s)
{
    std::cerr << "\033[1;37mInformation:\033[0m " << s << std::endl;
}

// Print error and exit.
void die(const char* e)     // Error to print out.
{
    std::cerr << e << std::endl;
    exit(errno);
}

// Print error.
void error(const std::string& s) // Error to print out.
{
    std::cout << "\033[1;31mError:\033[0m " << s << std::endl;
}

// Print error.
void error(const err& e)    // Error to print out.
{
    std::cout << "\033[1;31mError:\033[0m " << e << std::endl;
}

// Print operating system error.
void syserror(const std::string& s)
{
    error(s);  // TODO: Colorize.
    perror(0);
}

// Print warning.
void warn(const std::string& s)
{
    std::cout << "\033[1;33mWarning:\033[0m " << s << std::endl;
}

// Print warning.
void warn(const char *s) 
{
    std::cout << "\033[1;33mWarning:\033[0m " << s << std::endl;
}

// Color codes: https://en.wikipedia.org/wiki/ANSI_escape_code
