#include <cassert>
#include <algorithm>
#include <stdexcept>
#include "byteswap.hpp"
using namespace std;

// Swap the placement of two elements of the size of type T.
template<typename T>
void bswap(T* beg, T* const end) {
    assert(beg < end);
	while (beg < end) {
		swap(*beg, *(beg + 1));
        beg += 2;
    }
}

namespace {
    // Word-swap 32-bit words.
    void hwswap_words(u32 *dwords, const size_t n) {
    	bswap(rcast<u16*>(dwords), rcast<u16*>(dwords + n));
    }
    
    // Byte-swap 16-bit half-words.
    void bswap_hwords(Byte p[], const size_t n) {
        assert(!(n % 2));
    	bswap(p, p + n);
    }
    
    // Byte-swap each 16-bit half-words. Quite inefficient, but works.
    void bswap_hwords(u16 w[], const size_t n) {
    	auto end = rcast<Byte*>(w+n), beg = rcast<Byte*>(w);
    	bswap_hwords(beg, end - beg);
    }
    
    // Byteswap 32-bit.
    void bswap32(u32& val) {
    	val = (((val) & 0xFF) << 24) | ((((val) & 0xFF00) >> 8) << 16) | ((((val) & 0xFF0000) >> 16) << 8) | (((val) & 0xFF000000) >> 24);
    }
    
    // Byte-swap each 32-bit words.
    void bswap_words(u32 words[], const size_t n) {
    	// TODO: Do a parallel byte swap for speed?
    	for (size_t i = 0; i < n; i++)
    		bswap32(words[i]);
    }
}

// Get size/length of array in elements.
#define NSIZE(len, type) len / sizeof(type)

// Byteswap the data in the ROM to the correct endianness used by the host computer.
void rombswap(void*        rom, // Pointer to the bytes of the loaded ROM file in memory.
              const size_t n)   // The number of elements in the ROM.
{
    auto p = rcast<u32*>(rom);

    // Check endianness of the ROM header.
	switch (*p) {
	case 0x80371240: // .Z64 endianness.
		return; // Correct order.
	case 0x12408037:
		hwswap_words(p, NSIZE(n, u32));
		return;
	case 0x40123780: // .N64 endianness.
		bswap_words(p, NSIZE(n, u32));
		return;
	case 0x37804012: // V64 endianness.
		bswap_hwords(rcast<u16*>(rom), NSIZE(n, u16));
		return;
    default:
        break;
	} // Many emulators use this method to discover the loaded ROM file's endianness.

    // For loading the PIF Boot ROM:
	bswap_words(p, NSIZE(n, u32));
}
