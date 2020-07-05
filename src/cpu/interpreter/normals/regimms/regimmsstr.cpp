#include "regimmsstr.hpp"
#include <disassembler/strings.hpp>
#include <cpu/strings/strmacros.hpp>
#include <cpu/interpreter/instrstr.hpp>
#include <cpu/interpreter/normals/cop0/tlb/tblsize.hpp>

namespace {
	const char* undefs = "Undefined REGIMM-instruction: ";
	const char* strings[NDEFINSTR] {
		"bltz", "bgez", "btlzl", "bgezl", undefs, undefs, undefs, undefs,
		"tgei", "tgeiu", "tlti", "tltiu", "teqi", undefs, "tnei ", undefs,
		"bltzal ", "bgezal ", "bltzall ", "bgezall ", undefs, undefs, undefs, undefs,
		undefs, undefs, undefs, undefs, undefs, undefs, undefs, undefs,
		undefs, undefs, undefs, undefs, undefs, undefs, undefs, undefs,
		undefs, undefs, undefs, undefs, undefs, undefs, undefs, undefs,
		undefs, undefs, undefs, undefs, undefs, undefs, undefs, undefs,
		undefs, undefs, undefs, undefs, undefs, undefs, undefs, undefs,
	};

	STRTABLE(ops) {
		&rs_off, &rs_off, &rs_off, &rs_off, &undef, &undef, &undef, &undef,
		&rs_imm, &not_impl, &not_impl, &not_impl, &not_impl, &undef, &not_impl, &undef,
		&rs_off, &rs_off, &not_impl, &not_impl, &undef, &undef, &undef, &undef,
		&undef,  &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef,  &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef,  &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef,  &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef,  &undef, &undef, &undef, &undef, &undef, &undef, &undef,
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

std::string build_regimm(const Instr i) {
	const auto op(i.regimm());
	return ops[op](strings[op], i);
}
