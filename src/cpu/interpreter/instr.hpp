// The Nintendo 64 processor R4300i-processor supports only the instructions from MIPS I to III.
#pragma once
#include <sstream>
#include "op.hpp"
#include "../../data_types/types.hpp"
#include "instrsz.hpp"

enum class Special_opcode { // 6-bits.
// Arithmetic and Logic-instructions:
	MULTU = 0x19, // Multiply unsigned word.
	MULT = 0x18, // Multiply word.
	ADD = 0x20, // Add word.
	ADDU = 0x21, // Add unsigned word.
	SUB = 0x22, // Subtract word.
	SUBU = 0x23, // Subtract word unsigned.
	DOUBLEWORD_DIVIDE = 0x1E, // abbreviated as DDIV.
	DIV = 0x1A, // Divide word
	DIVU = 0x1B, // Divide unsigned word.
	AND	= 0x24,
	OR = 0x25,
	XOR	= 0x26, // abbreviated as XOR.
	SHIFT_WORD_LEFT_LOGICAL = 0x00, // abbreviated as SLL.
	BREAKPOINT = 0xD,  // abbreviated as BREAK.
	TRAP_IF_LESS_THAN = 0x32, // abbreviated as TLT.
// Branch-instructions:
	JUMP_REGISTER = 0x08, // abbreviated as JR.
	JALR = 0x9,
	JR = 0x8,
	MFHI = 0x10,
	MFLO = 0x12,
	MTHI = 0x11,
	MTLO = 0x13,
	NOR = 0x27,
	SLLV = 0x4,
	SLT = 0x2a,
	SLTU = 0x2b,
	SRA = 0x3,
	SRAV = 0x7,
	SRL = 0x2,
	SRLV = 0x6,
	TEQ = 0x34,
	TGE = 0x30,
	TGEU = 0x31,
	TLT = 0x32,
};

enum Regimms {
	BLTZ = 0,
	BGEZ = 1,
	BLTZL = 2,
	BGEZL = 3,
	TGEI = 8,
	TGEIU = 9,
	TLTI = 10,
	TLTIU = 11,
	TEQI = 12,
	TNEI = 14,
	BLTZAL = 16,
	BGEZAL = 17,
	BLTZALL = 18,
	BGEZALL = 19,
};

class Instr { // has to be exactly 32-bit, which is defined by the MIPS-standard.
public:
	Instr(const u32);

	// Extract the destination operand (also known as RD) from the instruction and returns it.
	uint rd() const;
	// Extract the source operand (also known as RS) from the instruction and returns it.
	uint rs() const; // abbreviated as rs.
	// Extract the target operand (also known as RT) from the instruction and returns it.
	uint rt() const;
	// Extract the immediate operand from the instruction and returns it.
	int imm() const;
	// Extract the base-operand from an instruction and returns it.
	uint base() const;
	// Extract the offset-operand from an instruction and returns it.
	int offset() const;
	// Extract the instruction-index and returns it.
	uint instr_idx() const;
	// Extract the shift amount-operand from the instruction and returns it.
	uint sa() const;
	// Extract the COP0-instruction and returns it.
	uint cop0() const;
	// Extract the low-order 5-bit TLB-opcode and returns it.
	uint tlb() const;

	// Extracts the opcode from a normal MIPS-instruction (no SPECIAL bits).
	Opcode normal() const;
	// Extract the opcode of a Register-immediate instruction and returns it.
	Regimms regimm() const;
	// Extracts the opcode from a MIPS-instruction with the SPECIAL bits and returns it.
	uint spec() const;

	// Extracts the opcode from a MIPS-instruction with the SPECIAL bits and returns it with strong typecheck.
	Special_opcode special() const;

	// Check if the instruction is one of those instructions with the special-field and returns it.
	bool is_special() const;
	// Check to see if the operation is a register-immediate operation and returns it.
	bool is_regimm() const;
	// Check to see if the operation is a COP0-instruction and returns it.
	bool is_cop0() const;
	// Check to see if the operation is a COP1-instruction and returns it.
	bool is_cop1() const;
	// Check to see if the operation is a COP2-instruction and returns it.
	bool is_cop2() const;
	// Check to see if the operation is a "No-Operation"/NOP.
	bool is_nop() const;

	// Converts this instruction to an unsigned 32-bit value.
	explicit operator u32() const;
	// Compare a 32-bit representation of the instruction with the instruction itself.
	friend bool operator==(const Instr&, const u32);
	friend bool operator==(const u32, const Instr&);
	// Insert a MIPS instruction into a ASCII-text I/O-stream
	friend std::ostream& operator<<(std::ostream& o, const Instr);
	// Insert a MIPS instruction into a wide character I/O-stream
	friend std::wostream& operator<<(std::wostream& o, const Instr);
private:
	// Each instruction in the MIPS ISA is of 32-bit fixed-width size.
	const u32 instr; 
};
