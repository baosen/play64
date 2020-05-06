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

typedef int64_t Dword; // 64-bit Double word.
typedef int32_t Word;  // 32-bit word.
typedef int16_t Halfword; // 16-bit half-word.
typedef char    Byte; // 8-bit byte.

#define rcast reinterpret_cast
#define scast static_cast
