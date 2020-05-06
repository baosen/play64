#include "../../../data_types/types.hpp"
#include "pif.hpp"
#include "../../mem.hpp"
#include <iostream>
using namespace std;

namespace {
    u8 pifmem[JOYCHANNEL_RAM_END-BOOT_ROM_START];
}

// The PIF RAM is used to write command blocks that commands the PIF to save values back to the PIF RAM.
namespace Pif {
    void reset() { zero(pifmem); }
    void set(const u32 i, const u32 val) {
        pifmem[i] = val;
        switch (pifmem[0x7fc]) { // Interface to the security chip.
        case 8: // Needs to write this value to this address or the N64 will lock.
            cout << "[PIF] Access granted!" << endl;
            break;
        }
    }
}