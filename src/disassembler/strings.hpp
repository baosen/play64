// TODO:
// - Remove unused builders.
// - Simplify into three types of statement string builders.
#pragma once
#include "../cpu/interpreter/instr.hpp"
#include "../data_types/types.hpp"
using namespace std;

#define DECLSTR(name) string name(const string&, const Instr);

// The MIPS-ISA has three types of instructions:
// 1. I-type (Immediate-type)
// | opcode | rs | rt | offset |
// 2. J-type (Jump-type)
// | opcode | instr_index |
// 3. R-type (Register-type)
// | opcode | rs | rt | rd | sa | function |
DECLSTR(rs_off)
DECLSTR(rd_rs_rt)
DECLSTR(rs_imm)
DECLSTR(rs_rt)
DECLSTR(jump)
DECLSTR(rt_off_base)
DECLSTR(frt_off_base)
DECLSTR(rt_imm)
DECLSTR(rt_rs_imm)
DECLSTR(source)
DECLSTR(rs_rt_off)
DECLSTR(rd_rt_sa)
DECLSTR(rd_rt_rs)
DECLSTR(rd_rs)
DECLSTR(rd)
DECLSTR(grt_crd)
DECLSTR(crt_grd)

// For floating-point instructions:
DECLSTR(rt_fs)

// For TLB instructions:
DECLSTR(tlb_instr)

// For unknown instructions:
DECLSTR(undef) // Undefined instruction.
DECLSTR(not_impl) // Not implemented.
