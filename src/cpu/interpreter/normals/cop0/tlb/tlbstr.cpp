#include "tblsize.hpp"
#include "../../../../../disassembler/strings.hpp"
#include "../../../instrstr.hpp"
#include "../../../../strings/strmacros.hpp"

namespace {
	const char* undef = "Undefined TLB-instruction: ";
	const char* strings[NDEFINSTR] {
		undef,   "tlbr", "tlbwi", undef, undef, undef, "tlbwr", undef,
		"tlbp", undef,   undef,    undef, undef, undef, undef,    undef,
		undef,   undef,   undef,    undef, undef, undef, undef,    undef,
		"eret", undef,   undef,    undef, undef, undef, undef,    undef,
		undef,   undef,   undef,    undef, undef, undef, undef,    undef,
		undef,   undef,   undef,    undef, undef, undef, undef,    undef,
		undef,   undef,   undef,    undef, undef, undef, undef,    undef,
		undef,   undef,   undef,    undef, undef, undef, undef,    undef,
	};
}

std::string build_tlb(const uint i) {
	return string(strings[i]);
}
