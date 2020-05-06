#pragma once
#include "memaddr.hpp"

namespace Vmem {
    memory_address map(const memory_address vaddr);
    void wr64(const memory_address vaddr, u64 val);
    void wr32(const memory_address vaddr, u32 val);
    void wr16(const memory_address vaddr, u16 val);
    void wr8(const memory_address vaddr, u8 val);
    u32 rd32(const memory_address vaddr);
    u16 rd16(const memory_address vaddr);
    u8 rd8(const memory_address vaddr);
}
