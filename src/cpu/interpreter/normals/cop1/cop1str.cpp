#include "cop1str.hpp"
#include "../../../strings/strmacros.hpp"
#include "../../../../disassembler/strings.hpp"
#include "../../instrstr.hpp"
#include "../../../../cpu/interpreter/normals/cop0/tlb/tblsize.hpp"
using namespace std;

namespace {
	const char* undefcop1 = "Undefined COP1-instruction: ";
	const char* strings[NDEFINSTR] {
		"mfc1", "dmfc1", "cfc1", undefcop1, "mtc1", "dmtc1", "ctc1", undefcop1,
		undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1,
		undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1,
		undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1, undefcop1,
	};
	STRTABLE(ops) {
		&not_impl, &not_impl, &rt_fs, &undef, &not_impl, &not_impl, &rt_fs, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
		&undef, &undef, &undef, &undef, &undef, &undef, &undef, &undef,
	};
}

string build_cop1(const Instr i) {
	auto op(i.cop0());
	return ops[op](strings[op], i);
}
