#pragma once
#include <string>
#include "instr.hpp"

typedef std::string (*instr_str_t)(const std::string&, const Instr);
