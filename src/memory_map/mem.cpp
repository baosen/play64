#include "mem.hpp"

void memzero(void *p, const size_t sz) {
    memset(p, 0, sz);
}
