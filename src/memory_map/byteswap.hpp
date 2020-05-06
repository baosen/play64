#pragma once
#include <cstdlib>
#include "../data_types/types.hpp"

// Byte-swap a Nintendo 64 ROM to the right endianness.
void rombswap(void* rom, const size_t nbytes);
