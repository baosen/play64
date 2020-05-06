#include "../cpu/interpreter/err.hpp"

// Print log message.
void log(const std::string& s);
void log(const char* s);

// Print message and exit.
void die(const int);
void die(const char*);

// Print error message.
void error(const std::string&);
void error(const err&);

// Print system error message.
void syserror(const std::string& s);

// Warn user about something happened.
void warn(const std::string& s);
void warn(const char*);
