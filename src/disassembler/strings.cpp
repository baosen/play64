#include <iomanip>
#include "../cpu/interpreter/instr.hpp"
#include "strings.hpp"
#include "tlbstr.hpp"
using namespace std;

namespace {
	stringstream asmy; // shared by all functions to eliminate redundant memory allocations.

	// Setup stringstream to build hex-strings.
	void hexify() {
		asmy << hex << showbase << internal << setfill('0');
		// showbase: Prefix hexadecimal with C++ literal constants e.g 0x for hex, 0 for octal and no prefix for decimals.
		// internal: Adjust field by inserting characters at an internal position,
		// which for numerical values is between the sign and/or numerical base and the number magnitude.
	}

    // Setup stringstream to build hex-strings.
    void hexify(stringstream& s) {
    	s << hex << showbase << internal << setfill('0');
    }

	// Setup stringstream to build decimal numbers.
	void setdec() { 
		asmy << dec; 
	}

	// Clear the buffer inside the stream to build a new string.
	void clear() { 
		asmy.str(""); 
	}

    // Setup stringstream.
	void setup() { 
		clear(); 
        setdec(); 
	}

    const char* gpr[] {
        "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"
    };
    
    // Returns the name of the ith general purpose register.
    string sgpr(const uint i) {
        if (i > sizeof(gpr)/sizeof(gpr[0]))
            return "Unknown";
        return gpr[i];
    }
}

#define STR(fmt) string fmt(const string& op, const Instr instr)

STR(not_impl) {
	clear();
	asmy << op << " (not implemented)";
	return asmy.str();
}

STR(tlb_instr) {
	return build_tlb(instr.tlb());
}

STR(undef) {
	clear();
	// Setup stringstream to build hex-strings.
	hexify();
	// Build hex-string.
	asmy << op << setw(10) << instr;
	return asmy.str();
}

STR(rs_imm) {
	setup();
	asmy << op << " " << instr.rs() << ", " << instr.imm();
	return asmy.str();
}

STR(rs_rt_off) {
	setup();
	asmy << op << " " << sgpr(instr.rs()) << ", " << sgpr(instr.rt()) << ", " << static_cast<s16>(instr.offset() << 2);
	return asmy.str();
}

STR(rd_rs_rt) {
	setup();
	asmy << op << " " << sgpr(instr.rd()) << ", " << sgpr(instr.rs()) << ", " << sgpr(instr.rt());
	return asmy.str();
}

STR(rs_off) {
	setup();
	asmy << op << " " << sgpr(instr.rs()) << ", " << static_cast<s16>(instr.offset() << 2);
	return asmy.str();
}

STR(rt_rs_imm) {
	setup();
	asmy << op << " " << sgpr(instr.rt()) << ", " << sgpr(instr.rs()) << ", " << static_cast<s16>(instr.imm());
	return asmy.str();
}

STR(rt_fs) {
	setup();
	asmy << op << " " << sgpr(instr.rt()) << ", f" << instr.rd(); 
	// rd = fs.
	return asmy.str();
}

#include "../cpu/interpreter/normals/cop0/cop0const.hpp"

// For MTC0-3 instructions:
// TODO: Tablify.
static string cop0_name(const int i) {
    switch (i) {
	case Index:
        return "Index";
    case Random: 
        return "Random";
    case EntryLo0: 
        return "EntryLo0";
    case EntryLo1:
        return "EntryLo1";
    case Context: 
        return "Context";
    case PageMask: 
        return "PageMask";
    case Wired:
        return "Wired";
    case BadVAddr: 
        return "BadVAddr";
    case Count: 
        return "Count";
    case EntryHi: 
        return "EntryHi";
    case Compare: 
        return "Compare";
    case Status: 
        return "Status";
    case Cause:
        return "Cause";
	case EPC: 
        return "EPC";
    case PrevID: 
        return "PrevID";
    case Config: 
        return "Config";
    case LLAddr: 
        return "LLAddr";
    case WatchLo: 
        return "WatchLo";
    case WatchHi: 
        return "WatchHi";
    case C0_XContext:
        return "XContext";
    case PErr: 
        return "PErr";
    case CacheErr: 
        return "CacheErr";
    case TagLo:
        return "TagLo";
    case TagHi: 
        return "TagHi";
    case ErrorEPC: 
        return "ErrorEPC";
    }
    return "Unknown";
}

STR(crt_grd) {
	setup();
	asmy << op << " " << cop0_name(instr.rt()) << ", " << sgpr(instr.rd());
	return asmy.str();
}

STR(grt_crd) {
	setup();
	asmy << op << " " << sgpr(instr.rt()) << ", " << cop0_name(instr.rd());
	return asmy.str();
}

STR(source) {
	clear();
	setup();
	asmy << op << " " << sgpr(instr.rs());
	return asmy.str();
}

STR(rt_off_base) {
	setup();
	asmy << op << " " << sgpr(instr.rt()) << ", " << instr.offset() << "(" << sgpr(instr.base()) << ')';
	return asmy.str();
}

STR(frt_off_base) {
	setup();
	asmy << op << " f" << instr.rt() << ", " << instr.offset() << "(r" << instr.base() << ')';
	return asmy.str();
}

STR(rt_imm) {
	setup();
	asmy << op << " " << sgpr(instr.rt()) << ", " << showbase << hex << instr.imm();
	return asmy.str();
}

STR(jump) {
	clear();
	hexify();
	asmy << op << ' ' << hex << showbase << setw(8) << instr.instr_idx();
	// 8 bytes in an address.
	return asmy.str();
}

STR(rs_rt) {
	setup();
	asmy << op << " " << sgpr(instr.rs()) << ", " << sgpr(instr.rt());
	return asmy.str();
}

// Floating-point unit (COP1) instructions:
string fpabs(const Instr i) {
	return "fabs not implemented yet...";
}

STR(rd_rt_sa) {
	setup();
	asmy << op << " " << sgpr(instr.rd()) << ", " << sgpr(instr.rt()) << ", " << instr.sa();
	return asmy.str();
}

STR(rd_rt_rs) {
	setup();
	asmy << op << " " << sgpr(instr.rd()) << ", " << sgpr(instr.rt()) << ", " << sgpr(instr.rs());
	return asmy.str();
}

STR(rd_rs) {
	setup();
	asmy << op << " " << sgpr(instr.rd()) << ", " << sgpr(instr.rs());
	return asmy.str();
}

STR(rd) {
	setup();
	asmy << op << " " << sgpr(instr.rd());
	return asmy.str();
}
