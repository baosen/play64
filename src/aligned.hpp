#pragma once
#include "data_types/types.hpp"

inline s64 align(const s64 addr) {
	return addr & 0xffffffff;
}

inline int lw_not_aligned(const s64 addr) {
	return addr & 3;
}

inline int not_aligned(const s64 addr) {
    return addr & 1;
}
