#include <iostream>
#include "ai.hpp"
#include "../mi/mi.hpp"
#include "../../mem.hpp"
#include "../rdram/rdram.hpp"
#include "../../../cpu/interpreter/err.hpp"
using namespace std;

/* AI Registers. */
//enum {
//	DACRATE	= 0x10, /* DAC rate 14-lsb*/
//	BITRATE	= 0x14, /* Bit rate 4-lsb */
//	STATUS_FIFO_FULL = 0x80000000, /* Bit 31: full */
//	STATUS_DMA_BUSY = 0x40000000 /* Bit 30: busy */
//};

const int MAXIMUM_AUDIO_BUFFER_SIZE = 262144; // Maximum audio buffer size in bytes.

namespace {
    u32 regs[6]    = {0};
    u32 addr       = 0;
    u32 len        = 0;
    u32 control    = 0;
    u32 buf[MAXIMUM_AUDIO_BUFFER_SIZE] = {0}; // http://hcs64.com/files/n64-hw.dox.

    // Copy data from DRAM address to audio buffer.
    void bufcp() {
        if (len > MAXIMUM_AUDIO_BUFFER_SIZE)
            throw err("AI length is too large!");
        if (!addr)
            throw err("AI DRAM address is NULL!");
        // Copies to the audio buffer.
        memcpy(buf, RDram::ram+addr, len);
    }
}

// 0x0450 0000 to 0x045F FFFF  Audio interface (AI) registers:
//        AI_BASE_REG - 0x04500000
namespace Ai {
    void reset() {
        zero(regs);
    }

//  0x0450 0000 to 0x0450 0003  AI_DRAM_ADDR_REG
//      AI DRAM address
//      (W): [23:0] starting RDRAM address (8B-aligned)
    WR(dram_addr) {
        addr = val;
    }

//  0x0450 0004 to 0x0450 0007  AI_LEN_REG
//      AI length
//      (RW): [14:0] transfer length (v1.0) - Bottom 3 bits are ignored
//            [17:0] transfer length (v2.0) - Bottom 3 bits are ignored
    WR(len) {
        len = val & 3;
        if (control & 1) // DMA enabled?
            bufcp();
    }

//  0x0450 0008 to 0x0450 000B  AI_CONTROL_REG
//      AI control
//      (W): [0] DMA enable - if LSB == 1, DMA is enabled
    WR(control) {
        control = val;
        if (control & 1) // Is DMA enabled?
            puts("[AI] DMA is enabled!");
    }

//  0x0450 000C to 0x0450 000F  AI_STATUS_REG
//           AI status
//      (R): [31]/[0] ai_full (addr & len buffer full)
//           [30] ai_busy
//           Note that a 1to0 transition in ai_full will set interrupt
//      (W): clear audio interrupt
    RD(status) {
        return regs[3];
    }
    WRANY(status) {
        cout << "[AI] Clear AI interrupt." << endl;
        Mi::clearAI();
    }

//  0x0450 0010 to 0x0450 0013  AI_DACRATE_REG
//           AI DAC sample period register
    WR(dacrate) {
        regs[4] = val;
    }
//  (W): [13:0] dac rate
//           - video clock/(dperiod + 1) is the DAC sample rate
//           - (dperiod + 1) >= 66 * (aclockhp + 1) must be true

//  0x0450 0014 to 0x0450 0017  AI_BITRATE_REG
//           AI bit rate
    WR(bitrate) {
        regs[5] = val;
    }
//  (W): [3:0] bit rate (abus clock half period register - aclockhp)
//           - vid_clock/(2*(aclockhp + 1)) is the DAC clock rate
//           - The abus clock stops if aclockhp is zero

//  0x0450 0018 to 0x045F FFFF  Unused
}
