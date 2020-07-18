#pragma once
#include <cstdint>

inline int64_t align(const int64_t addr) {
	return addr & 0xffffffff;
}

inline int lw_not_aligned(const int64_t addr) {
	return addr & 3;
}

inline int not_aligned(const int64_t addr) {
    return addr & 1;
}
