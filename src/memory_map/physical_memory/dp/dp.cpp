#include "dp.h"

// Reality Display Processor.
// This is Nintendo 64's rasterizer.
namespace {
}

namespace Dp {
    //  DPC_BASE_REG - 0x04100000

    // 0x04100000 to 0x04100003  DPC_START_REG //DP CMD DMA start
    RD(start) {
        return 0;
    }
    WR(start) {
    }
    //    (RW): [23:0] DMEM/RDRAM start address

    // 0x04100004 to 0x04100007  DPC_END_REG //DP CMD DMA end
    RD(end) {
        return 0;
    }
    WR(end) {
    }
    //    (RW): [23:0] DMEM/RDRAM end address

    // 0x04100008 to 0x0410000B  DPC_CURRENT_REG //DP CMD DMA end
    RD(current) {
        return 0;
    }
    WR(current) {
    }
    //     (R): [23:0] DMEM/RDRAM current address

    // 0x0410000C to 0x0410000F  DPC_STATUS_REG //DP CMD status
    RD(status) {
        return 0;
    }
    WR(status) {
    }
    //     (W): [0] clear xbus_dmem_dma  (R): [0]  xbus_dmem_dma
    //          [1] set xbus_dmem_dma         [1]  freeze
    //          [2] clear freeze              [2]  flush
    //          [3] set freeze                [3]  start gclk
    //          [4] clear flush               [4]  tmem busy
    //          [5] set flush                 [5]  pipe busy
    //          [6] clear tmem ctr            [6]  cmd busy
    //          [7] clear pipe ctr            [7]  cbuf ready
    //          [8] clear cmd ctr             [8]  dma busy
    //          [9] clear clock ctr           [9]  end valid
    //                                        [10] start valid

    // 0x04100010 to 0x04100013  DPC_CLOCK_REG //DP clock counter
    RD(clock) {
        return 0;
    }
    WR(clock) {
    }
    //     (R): [23:0] clock counter

    // 0x04100014 to 0x04100017  DPC_BUFBUSY_REG //DP buffer busy counter
    RD(bufbusy) {
        return 0;
    }
    WR(bufbusy) {
    }
    //     (R): [23:0] clock counter

    // 0x04100018 to 0x0410001B  DPC_PIPEBUSY_REG //DP pipe busy counter
    RD(pipebusy) {
        return 0;
    }
    WR(pipebusy) {
    }
    //     (R): [23:0] clock counter

    // 0x0410001C to 0x0410001F  DPC_TMEM_REG //DP TMEM load counter
    RD(tmem) {
        return 0;
    }
    WR(tmem) {
    }
    //     (R): [23:0] clock counter

    // 0x0410 0020 to 0x041F FFFF * Unused

    // DPS_BASE_REG - 0x04200000
    RD(base) {
        return 0;
    }
    WR(base) {
    }

    // 0x04200000 to 0x04200003  DPS_TBIST_REG //DP tmem bist
    RD(tbist) {
        return 0;
    }
    WR(tbist) {
    }
    //     (W): [0] BIST check           (R): [0] BIST check
    //          [1] BIST go                [1] BIST go
    //          [2] BIST clear             [2] BIST done
    //                                        [3-10] BIST fail

    // 0x04200004 to 0x04200007  DPS_TEST_MODE_REG //DP span test mode
    RD(test_mode) {
        return 0;
    }
    WR(test_mode) {
    }
    //     (RW): [0] Span buffer test access enable

    // 0x04200008 to 0x0420000B  DPS_BUFTEST_ADDR_REG //DP span buffer test address
    RD(buftest_addr) {
        return 0;
    }
    WR(buftest_addr) {
    }
    //     (RW): [6:0] bits

    // 0x0420000C to 0x0420000F  DPS_BUFTEST_DATA_REG //DP span buffer test data
    RD(buftest_data) {
        return 0;
    }
    WR(buftest_data) {
    }
    //     (RW): [31:0] span buffer data

    // 0x04200010 to 0x042FFFFF * Unused
}