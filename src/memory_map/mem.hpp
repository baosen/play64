#pragma once
#include <cstring>

// Zero out space of given length in bytes pointed by p.
void memzero(void *p, const size_t len);

// Zero out object.
template<class T>
void zero(T& o) {
    memzero(&o, sizeof o);
}
