#include "../memaddr.hpp"
namespace Physmem {
    void wr64(const memory_address paddr, const u64 val);
    void wr32(const memory_address paddr, const u32 val);
    void wr16(const memory_address paddr, const u16 val);
    void wr8(const memory_address paddr, const u8 val);
    u32 rd32(const memory_address paddr);
    u16 rd16(const memory_address paddr);
    u8 rd8(const memory_address paddr);
}
