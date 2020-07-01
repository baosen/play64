#include "cop0str.hpp"
#include "../../../../disassembler/strings.hpp"
#include "../../instrstr.hpp"
#include "tlb/tblsize.hpp"
#include "../../../strings/strmacros.hpp"

namespace {
	const char* undefcop0 = "Undefined COP0-instruction: ";

	const char* strings[NDEFINSTR] {
		"mfc0",    undefcop0, undefcop0, undefcop0, "mtc0",    undefcop0, undefcop0, undefcop0,
		undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0,
		"tlb",     undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0,
		undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0, undefcop0,
	};

	STRTABLE(ops) {
		&crt_grd,   &not_impl, &not_impl, &undef, &grt_crd, &not_impl, &not_impl, &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&tlb_instr, &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
		&undef,     &undef,    &undef,    &undef, &undef,   &undef,    &undef,    &undef,
	};
}

string build_cop0(const Instr i) {
	const auto opc = i.cop0();
	return ops[opc](strings[opc], i);
}
