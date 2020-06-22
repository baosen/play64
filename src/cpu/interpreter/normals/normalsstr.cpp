#include "normalsstr.hpp"
#include "../../../disassembler/strings.hpp"
#include "../../tlb/tblsize.hpp"
#include "../instrstr.hpp"
#include "../../strings/strmacros.hpp"

namespace {
	const char* undefs = "Undefined normal instruction: ";
	const char* str[NDEFINSTR] {
		"special", "regimm", "j",    "jal",   "beq",  "bne",  "blez",  "bgtz",
		"addi",    "addiu",  "slti", "sltiu", "andi", "ori",  "xori",  "lui",
		"cop0",    "cop1",   "cop2", undefs,   "beql", "bnel", "blezl", "bgtzl",
		"daddi",   "daddiu", "ldl",  "ldr",   undefs,  undefs,  undefs,   undefs,
		"lb",      "lh",     "lwl",  "lw",    "lbu",  "lhu",  "lwr",   "lwu",
		"sb",      "sh",     "swl",  "sw",    "sdl",  "sdr",  "swr",   "cache", 
		"ll",      "lwc1",   "lwc2", undefs,   "lld",  "ldc1", "ldc2",  "ld", 
		"sc",      "swc1",   "swc2", undefs,   "scd",  "sdc1", "sdc2",  "sd",
	};

	// Implements the MIPS III-architecture opcode matrix.
	STRTABLE(ops) {
		&undef,       &undef,        &jump,          &jump,         &rs_rt_off,     &rs_rt_off,    &rs_off,      &rs_off,
		&rt_rs_imm,   &rt_rs_imm,    &rt_rs_imm,     &rt_rs_imm,    &rt_rs_imm,     &rt_rs_imm,    &rt_rs_imm,   &rt_imm, 
		&undef,       &undef,        &undef, &undef, &rs_rt_off,    &rs_rt_off,     &rs_off,       &rs_off,
		&rt_rs_imm,   &rt_rs_imm,    &rt_off_base,   &frt_off_base, &undef, &undef, &undef,		   &undef,
		&rt_off_base, &rt_off_base,  &rt_off_base,   &rt_off_base,  &rt_off_base,   &rt_off_base,  &rt_off_base, &rt_off_base,
		&rt_off_base, &rt_off_base,  &rt_off_base,   &rt_off_base,  &rt_off_base,   &rt_off_base,  &rt_off_base, &not_impl,
		&rt_off_base, &frt_off_base, &rt_off_base,   &undef,	    &rt_off_base,   &frt_off_base, &rt_off_base, &rs_rt_off,
		&rt_off_base, &frt_off_base, &rt_off_base,   &undef,   	    &rt_off_base,   &frt_off_base, &not_impl,    &rt_off_base,
	};

	STRTABLE(hops) {
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
		&undef,&undef,&undef,&undef,&undef,&undef,&undef,&undef,
	};
}

// Build normal instruction string.
string build_normal(const Instr i) {
	const auto op(static_cast<uint>(i.normal()));
	return ops[op](str[op], i);
}
