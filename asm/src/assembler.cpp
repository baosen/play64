// TODO: Check if assembling r0-assignment on some instructions that requires it.
#include <assembler.hpp>
#include "op.hpp"
#include "specials.hpp"
#include "regimms.hpp"
#include <instr/bitpos.hpp>
#include <cstdint>

#define REGTYPE_CALL dest, source, target

#define DEFINE_REGISTER_IMMEDIATE_TYPE(name, op) \
	Instr name(REGTYPE_PARAMS) { \
		return reg_type((op), REGTYPE_CALL); \
	}

#define OR_IMMEDIATE_PARAMETERS source(src) | target(rt) | immediate(imm)

#define DEFINE_IMMEDIATE_TYPE(name, op) \
	Instr name(IMM_TYPE_PARAMS) { \
		return opcode(op) | OR_IMMEDIATE_PARAMETERS; \
	}

#define DEFINE_JUMP_TYPE(name, op) \
	Instr name(int32_t memory_address) { \
		return opcode(op) | instr_idx(memory_address); \
	}

#define DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(name, op) \
	Instr name(unsigned int rs, unsigned int off) { \
		return regimm(op) | source(rs) | offset(off); \
	}

#define DEFINE_SOURCE_OFFSET(name, op) \
	Instr name(unsigned int src, unsigned int off) { \
		return opcode(op) | source(src) | offset(off); \
	}

#define DEFINE_SOURCE_TARGET_TYPE(name , op) \
	Instr name(unsigned int rs, unsigned int rt) { \
		return source(rs) | target(rt) | static_cast<unsigned int>(op); \
	}

namespace assembler {
	unsigned int shiftamt(unsigned int value) {
		return value << 6;
	}
	unsigned int base(unsigned int value) {
		return value << SRC_POS;
	}
	unsigned int hint(unsigned int value) {
		return value << 6;
	}

	int offset(int off) {
		return off & 0xffff;
	}

	int32_t regimm(unsigned int op) {
		return (1 << (5 + 5 + 16)) | op << 16;
	}

	int32_t instr_idx(int32_t addr) { 
		return addr & 0x7FFFFFF; 
	}

	int32_t opcode(Opcode op) { 
		return op << OPCODE_POS; 
	}

	unsigned int dest(unsigned int destination) { 
		return destination << DEST_POS; 
	}
	unsigned int source(unsigned int src) { 
		return src << SRC_POS; 
	}

// TODO: Ask mask to them for error-recovery.
	unsigned int target(unsigned int rt) { 
		return rt << TARGET_POS; 
	}

	unsigned int immediate(int imm) { 
		return imm & 0xffff; 
	}

	// Set the register numbers.
	unsigned int set(unsigned int dst, unsigned int src, unsigned int rt) { 
		return dest(dst) | source(src) | target(rt); 
	}

	unsigned int reg_type(Special_opcode op, REGTYPE_PARAMS) {
		return static_cast<unsigned int>(op) | set(REGTYPE_CALL); 
	}

	Instr nop() { 
		return NOP; 
	}
	Instr jalr(unsigned int rd, unsigned int rs, unsigned int hint) {
		return dest(rd) | source(rs) | (hint << 6) | static_cast<unsigned int>(Special_opcode::JALR);
	}

#define DEFINE_DESTINATION_TYPE(name, op) \
	Instr name(unsigned int rd) { \
		return dest(rd) | static_cast<unsigned int>(op); \
	}

	DEFINE_DESTINATION_TYPE(mfhi, Special_opcode::MFHI)
	DEFINE_DESTINATION_TYPE(mflo, Special_opcode::MFLO)

#define DEFINE_SOURCE_TYPE(name, op) \
	Instr name(unsigned int rs) { \
		return source(rs) | static_cast<unsigned int>(op); \
	}

	DEFINE_SOURCE_TYPE(mthi, Special_opcode::MTHI)
	DEFINE_SOURCE_TYPE(mtlo, Special_opcode::MTLO)

	Instr nor(unsigned int rd, unsigned int rs, unsigned int rt) {
		return dest(rd) | source(rs) | target(rt) | static_cast<unsigned int>(Special_opcode::NOR);
	}

	DEFINE_IMMEDIATE_TYPE(addi, ADDI)
	DEFINE_IMMEDIATE_TYPE(addiu, ADDIU)
	DEFINE_IMMEDIATE_TYPE(andi, ANDI)
	DEFINE_IMMEDIATE_TYPE(beq, BEQ)
	DEFINE_IMMEDIATE_TYPE(beql, BEQL)
	DEFINE_IMMEDIATE_TYPE(bne, BNE)
	DEFINE_IMMEDIATE_TYPE(bnel, BNEL)

	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bgez, BGEZ)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bgezal, BGEZAL)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bgezall, BGEZALL)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bgezl, BGEZL)

	DEFINE_SOURCE_OFFSET(bgtz, BGTZ)
	DEFINE_SOURCE_OFFSET(bgtzl, BGTZL)
	DEFINE_SOURCE_OFFSET(blez, BLEZ)
	DEFINE_SOURCE_OFFSET(blezl, BLEZL)

	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bltz, BLTZ)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bltzal, BLTZAL)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bltzall, BLTZALL)
	DEFINE_SOURCE_OFFSET_REGISTER_IMMEDIATE_TYPE(bltzl, BLTZL)
	DEFINE_JUMP_TYPE(j, J)
	DEFINE_JUMP_TYPE(jal, JAL)
	DEFINE_REGISTER_IMMEDIATE_TYPE(And, Special_opcode::AND)
	DEFINE_REGISTER_IMMEDIATE_TYPE(Or, Special_opcode::OR)
	DEFINE_REGISTER_IMMEDIATE_TYPE(Xor, Special_opcode::XOR)

	Instr jr(unsigned int rs, unsigned int h) {
		return source(rs) | hint(h) | static_cast<unsigned int>(Special_opcode::JR);
	}

#define DEFINE_TARGET_OFFSET_BASE_TYPE(name, op) \
	Instr name(unsigned int rt, unsigned int off, unsigned int b) { \
		return opcode(op) | base(b) | target(rt) | offset(off); \
	}

	DEFINE_TARGET_OFFSET_BASE_TYPE(lb, LB)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lbu, LBU)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lh, LH)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lhu, LHU)
	DEFINE_TARGET_OFFSET_BASE_TYPE(ll, LL)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lw, LW)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lwl, LWL)
	DEFINE_TARGET_OFFSET_BASE_TYPE(lwr, LWR)
	DEFINE_TARGET_OFFSET_BASE_TYPE(sb, SB)
	DEFINE_TARGET_OFFSET_BASE_TYPE(sc, SC)
	DEFINE_TARGET_OFFSET_BASE_TYPE(sh, SH)
	DEFINE_TARGET_OFFSET_BASE_TYPE(sw, SW)
	DEFINE_TARGET_OFFSET_BASE_TYPE(swc1, SWC1)
	DEFINE_TARGET_OFFSET_BASE_TYPE(swc2, SWC2)
	DEFINE_TARGET_OFFSET_BASE_TYPE(swl, SWL)
	DEFINE_TARGET_OFFSET_BASE_TYPE(swr, SWR)

	DEFINE_REGISTER_IMMEDIATE_TYPE(add, Special_opcode::ADD)
	DEFINE_REGISTER_IMMEDIATE_TYPE(addu, Special_opcode::ADDU)
	DEFINE_REGISTER_IMMEDIATE_TYPE(sub, Special_opcode::SUB)
	DEFINE_REGISTER_IMMEDIATE_TYPE(subu, Special_opcode::SUBU)

	DEFINE_SOURCE_TARGET_TYPE(mult, Special_opcode::MULT)
	DEFINE_SOURCE_TARGET_TYPE(multu, Special_opcode::MULTU)
	DEFINE_SOURCE_TARGET_TYPE(div, Special_opcode::DIV)
	DEFINE_SOURCE_TARGET_TYPE(divu, Special_opcode::DIVU)
	DEFINE_SOURCE_TARGET_TYPE(tgeu, Special_opcode::TGEU)
	DEFINE_SOURCE_TARGET_TYPE(tlt, Special_opcode::TLT)
	DEFINE_SOURCE_TARGET_TYPE(teq, Special_opcode::TEQ)
	DEFINE_SOURCE_TARGET_TYPE(tge, Special_opcode::TGE)

	Instr lui(unsigned int rt, unsigned int imm) {
		return opcode(LUI) | target(rt) | immediate(imm);
	}

#define DEFINE_TARGET_SOURCE_IMMEDIATE(name, op) \
	Instr name(unsigned int rt, unsigned int rs, unsigned int imm) { \
		return opcode(op) | target(rt) | source(rs) | immediate(imm); \
	}

	DEFINE_TARGET_SOURCE_IMMEDIATE(ori, ORI)
	DEFINE_TARGET_SOURCE_IMMEDIATE(xori, XORI)
	DEFINE_TARGET_SOURCE_IMMEDIATE(slti, SLTI)
	DEFINE_TARGET_SOURCE_IMMEDIATE(sltiu, SLTIU)

#define DEFINE_DESTINATION_TARGET_SOURCE_TYPE(name, op) \
	Instr name(unsigned int rd, unsigned int rt, unsigned int rs) { \
		return dest(rd) | target(rt) | source(rs) | static_cast<unsigned int>(op); \
	}

	DEFINE_DESTINATION_TARGET_SOURCE_TYPE(sltu, Special_opcode::SLTU)
	DEFINE_DESTINATION_TARGET_SOURCE_TYPE(srav, Special_opcode::SRAV)
	DEFINE_DESTINATION_TARGET_SOURCE_TYPE(sllv, Special_opcode::SLLV)
	DEFINE_DESTINATION_TARGET_SOURCE_TYPE(slt, Special_opcode::SLT)
	DEFINE_DESTINATION_TARGET_SOURCE_TYPE(srlv, Special_opcode::SRLV)

#define DEFINE_DESTINATION_TARGET_SHIFTAMOUNT(name, op) \
	Instr name(unsigned int rd, unsigned int rt, unsigned int sa) { \
		return target(rt) | dest(rd) | shiftamt(sa) | static_cast<unsigned int>(op); \
	}

	DEFINE_DESTINATION_TARGET_SHIFTAMOUNT(sll, Special_opcode::SHIFT_WORD_LEFT_LOGICAL)
	DEFINE_DESTINATION_TARGET_SHIFTAMOUNT(sra, Special_opcode::SRA)
	DEFINE_DESTINATION_TARGET_SHIFTAMOUNT(srl, Special_opcode::SRL)

#define DEFINE_SOURCE_IMMEDIATE(name, op) \
	Instr name(unsigned int rs, unsigned int imm) { \
		return source(rs) | regimm(op)| immediate(imm); \
	}

	DEFINE_SOURCE_IMMEDIATE(teqi, TEQI)
	DEFINE_SOURCE_IMMEDIATE(tgei, TGEI)
	DEFINE_SOURCE_IMMEDIATE(tgeiu, TGEIU)
}
