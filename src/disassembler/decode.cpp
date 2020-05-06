#include "../cpu/interpreter/normals/normalsstr.hpp"
#include "../cpu/interpreter/specials/specialsstr.hpp"
#include "../cpu/interpreter/regimms/regimmsstr.hpp"
#include "../cpu/cop1/cop1str.hpp"
#include "../cpu/cop0/cop0str.hpp"
using namespace std;

// Decode instruction returning its string in high-level syntax.
string hdec(const Instr i) {
    // Check if it is a "No operation"-instruction.
    if (i.is_nop())
        return "nop";
    // Decode SPECIAL-opcodes (opcodes that has the SPECIAL-bits 0000000 in its normal opcode-field).
    if (i.is_special())
    // Decode Register-Immediate instructions.
    if (i.is_regimm())
    // System control processor.
    if (i.is_cop0())
    // Decode Coprocessor 1-instructions, which is the floating point-coprocessor:
    if (i.is_cop1())
    // RSP's vector instructions.
    if (i.is_cop2())
        return "Unknown COP2-instruction!";
    return build_normal(i);
}

// Decode an MIPS instruction. Return the decoded instruction as a string.
string decode(const Instr i) {
	// Check if it is a "No operation"-instruction.
	if (i.is_nop())
		return "nop";
	// Decode SPECIAL-opcodes (opcodes that has the SPECIAL-bits 0000000 in its normal opcode-field).
	if (i.is_special())
		return build_special(i);
	// Decode Register-Immediate instructions.
	if (i.is_regimm())
		return build_regimm(i);
	// System control processor.
	if (i.is_cop0())
		return build_cop0(i);
	// Decode Coprocessor 1-instructions, which is the floating point-coprocessor:
	if (i.is_cop1())
		return build_cop1(i);
	// RSP's vector instructions.
	if (i.is_cop2())
		return "Unknown COP2-instruction!";
	return build_normal(i);
}
