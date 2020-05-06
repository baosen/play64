#include "rdram.hpp"
#include "../../cpu/interpreter/err.hpp"
#include "../mem.hpp"

// RDRAM Registers (0x03f00000 .. 0x03ffffff).
//enum {
	//0_DEVICE_ID	0
	//1_DEVICE_ID	1

	//RESET_MODE        0
	//ACTIVE_MODE       1
	//STANDBY_MODE      2

	//LENGTH		(2*512*2048)
	//0_BASE_ADDRESS	(RDRAM_0_DEVICE_ID*RDRAM_LENGTH)
	//1_BASE_ADDRESS	(RDRAM_1_DEVICE_ID*RDRAM_LENGTH)

	//0_CONFIG		0x00000
	//1_CONFIG		0x00400
	//GLOBAL_CONFIG	0x80000
//};

// RDRAM physical memory map:
enum {
// 0x0000_0000 .. 0x03ef_ffff: RDRAM memory.
	MEMORY_END		= 0x3fffff,
// 0x03f0_0000 .. 0x03ff_ffff: RDRAM registers.
	REGISTERS_START = 0x3f00000,
};

enum {
    CONFIG_OR_TYPE = 0,
    DEVICE_ID = 4,
    DELAY = 8,
    MODE = 0xc,
    REF_INTERVAL = 0x10,
    REF_ROW = 0x14,
    RAS_INTERVAL = 0x18,
    MIN_INTERVAL = 0x1c,
    ADDRESS_SELECT = 0x20,
    DEVICE_MANUFACTURER = 0x24,
};

// The Nintendo 64's main memory that contains four megabytes of "nine bit" DRAMS.
// The hidden ninth bit is used by the anti-aliasing and z-buffering hardware.
namespace RDram {
	char ram[MEMORY_END];

    void reset() { zero(ram); }
    u32 rd32(const uint i) { return ram[i]; }
    void wr32(const uint i, const u32 val) { ram[i] = val; }
}

/*
namespace {
    char regs[0x3f00027-0x3f00000];
}

namespace RDramregs {
    u32 rd32(const int i) {}
    void wr32(const int i, const u32 val) {}
}
*/
