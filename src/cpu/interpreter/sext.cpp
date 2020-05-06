#include "sext.hpp"

// Sign-extend 8-bit.
s64 sext8(s64 b) {
    return (b >> 7) & 1 ? ~0xff | b : b;
}

// Sign-extend 16-bit.
s64 sext16(s64 b) {
	return ((b & 0xffff) >> 15) ? 0xffffffffffff0000 | b : b;
}

// Sign-extend the 18-bit value by duplicating the 31 upper bit towards the left end of the bit-string.
s64 sext18(s64 b) {
	return ((b & 0x3ffff)) >> 17 ? (0xfffffffffffc0000LL | b) : b;
}

// Sign-extend 32-bit.
s64 sext32(s64 b) {
	return ((b >> 31) & 1) ? (0xffffffff00000000 | b) : b;
}
