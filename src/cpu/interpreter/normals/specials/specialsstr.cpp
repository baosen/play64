#include "../../../../disassembler/strings.hpp"
#include "specials.hpp"
#include "../../instrstr.hpp"
#include "../../../tlb/tblsize.hpp"
#include "../../../strings/strmacros.hpp"
using namespace std;

namespace {
	const char* undefs = "Undefined SPECIAL-instruction: ";
	const char* strings[NDEFINSTR] {
		"sll",  undefs,  "srl",  "sra",   "sllv",    undefs,   "srlv",   "srav",
		"jr",   "jalr",  undefs,  undefs, "syscall", "break",  undefs,   "sync",
		"mfhi", "mthi",  "mflo", "mtlo",  "dsllv",   undefs,   "dsrlv",  "dsrav",
		"mult", "multu", "div",  "divu",  "dmult",   "dmultu", "ddiv",   "ddivu",
		"add",  "addu",  "sub",  "subu",  "and",     "or",     "xor",    "nor",
		undefs,  undefs, "slt",  "sltu",  "dadd",    "daddu",  "dsub",   "dsubu",
		"tge",  "tgeu",  "tlt",  "tltu",  "teq",     undefs,   "tne",     undefs,
		"dsll", undefs,  "dsrl", "dsra",  "dsll32",  undefs,   "dsrl32", "dsra32",
	};

	STRTABLE(ops) {
		&rd_rt_sa, &undef,    &rd_rt_sa, &rd_rt_sa, &rd_rt_rs, &undef,    &rd_rt_rs, &rd_rt_rs,
		&source,   &rd_rs,    &undef,    &undef,    &not_impl, &not_impl, &undef,    &not_impl,
		&rd,       &source,   &rd,       &source,   &rd_rt_rs, &undef,    &rd_rt_rs, &rd_rt_rs,
		&rs_rt,    &rs_rt,    &rs_rt,    &rs_rt,    &rs_rt,    &rs_rt,    &rs_rt,    &rs_rt,
		&rd_rs_rt, &rd_rs_rt, &rd_rs_rt, &rd_rs_rt, &rd_rs_rt, &rd_rs_rt, &rd_rs_rt, &rd_rs_rt,
		&undef,    &undef,    &not_impl, &rd_rs_rt, &not_impl, &not_impl, &not_impl, &not_impl,
		&not_impl, &not_impl, &not_impl, &not_impl, &not_impl, &undef,    &not_impl, &undef,
		&rd_rt_sa, &undef,    &rd_rt_sa, &rd_rt_sa, &rd_rt_sa, &undef,    &rd_rt_sa, &rd_rt_sa,
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

string build_special(const Instr i) {
	const auto op(static_cast<uint>(i.special()));
	return ops[op](strings[op], i);
}
