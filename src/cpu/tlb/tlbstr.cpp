#include "../../disassembler/strings.hpp"
#include "../interpreter/instrstr.hpp"
#include "tblsize.hpp"
#include "../strings/strmacros.hpp"
using namespace std;

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

string build_tlb(const uint i) {
	return string(strings[i]);
}
