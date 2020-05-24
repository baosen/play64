#pragma once
#include <cstdint>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef unsigned int uint;

// MIPS data types:
typedef int64_t Dword;    // Double word. 64-bit.
typedef int32_t Word;     // Word. 32-bit.
typedef int16_t Halfword; // Half-word. 16-bit.
typedef char    Byte;     // Byte. 8-bit.

#define rcast reinterpret_cast
#define scast static_cast
