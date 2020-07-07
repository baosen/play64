#include <cpu/interpreter/normals/normalsstr.hpp>
#include <cpu/interpreter/normals/specials/specialsstr.hpp>
#include <cpu/interpreter/normals/regimms/regimmsstr.hpp>
#include <cpu/interpreter/normals/cop1/cop1str.hpp>
#include <cpu/interpreter/normals/cop0/cop0str.hpp>

// Decode an MIPS instruction. Return the decoded instruction as a string.
std::string decode(const Instr instruction_to_decode) {
	// Check if it is a "No operation"-instruction.
	if (instruction_to_decode.is_nop()) {
		return "nop";
	}

	// Decode SPECIAL-opcodes (opcodes that has the SPECIAL-bits 0000000 in its normal opcode-field).
	if (instruction_to_decode.is_special()) {
		return build_special(instruction_to_decode);
	}

	// Decode Register-Immediate instructions.
	if (instruction_to_decode.is_regimm()) {
		return build_regimm(instruction_to_decode);
	}

	// System control processor.
	if (instruction_to_decode.is_cop0()) {
		return build_cop0(instruction_to_decode);
	}

	// Decode Coprocessor 1-instructions, which is the floating point-coprocessor:
	if (instruction_to_decode.is_cop1()) {
		return build_cop1(instruction_to_decode);
	}

	// RSP's vector instructions.
	if (instruction_to_decode.is_cop2()) {
		return "Unknown COP2-instruction!";
	}

	return build_normal(instruction_to_decode);
}
