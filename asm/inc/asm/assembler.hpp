#pragma once

// TODO:
// - Create macros for functions that are alike.

#include "instr.hpp"
#include "types.hpp"

#define REGTYPE_PARAMS \
    uint dest, uint source, uint target
#define DECLARE_REGISTER_TYPE_INSTRUCTION(name) \
	Instr name(REGTYPE_PARAMS)

#define IMM_TYPE_PARAMS \
    uint rt, uint src, int imm
#define DECLARE_IMMEDIATE_TYPE_INSTRUCTION(name) \
	Instr name(IMM_TYPE_PARAMS)

#define DECLARE_JUMP_TYPE_INSTRUCTION(name) \
	Instr name(s32 addr)
#define DECL_JTYPE_HINT(name) \
	Instr name(u32 addr, uint hint = 0)

#define DECLARE_SOURCE_OFFSET_INSTRUCTION(name) \
	Instr name(uint rs, uint off)

namespace assembler {
// Functions for placing values into the right bit-positions:
	uint shiftamt(uint value);
	uint hint(uint val);
	uint base(uint val);
	int offset(int off);
	s32 regimm(uint op);
	s32 instr_idx(s32 addr);
	s32 opcode(Opcode op);
	uint dest(uint dest);
	uint source(uint src);
	uint target(uint rt);
	uint immediate(int imm);
	uint set(uint dst, uint src, uint rt);
	uint reg_type(Special_opcode op, REGTYPE_PARAMS);

	Instr nop();
	DECLARE_JUMP_TYPE_INSTRUCTION(j);
	DECLARE_JUMP_TYPE_INSTRUCTION(jal);
	Instr jalr(uint rd, uint rs, uint hint = 0);
	Instr jr(uint rs, uint hint = 0);

#define DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(name) \
	Instr name(uint rt, uint off, uint base)

	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(lb);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(lbu);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(lh);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(lhu);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(ll);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(lw);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(sb);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(sc);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(sh);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(sw);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(swc2);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(swl);
	DECLARE_TARGET_OFFSET_BASE_INSTRUCTION(swr);

	Instr lui(uint rt, uint imm);

#define DEFINE_BASE_TARGET_OFFSET(name) \
	Instr name(uint base, uint rt, uint off)

	DEFINE_BASE_TARGET_OFFSET(lwl);
	DEFINE_BASE_TARGET_OFFSET(lwr);

	Instr mfhi(uint rd);
	Instr mflo(uint rd);
	Instr mthi(uint rs);
	Instr mtlo(uint rs);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(beq);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(beql);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(bne);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(bnel);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgez);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgezal);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgezall);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgezl);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgtz);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bgtzl);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(blez);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(blezl);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bltz);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bltzal);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bltzall);
	DECLARE_SOURCE_OFFSET_INSTRUCTION(bltzl);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(addi);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(addiu);
	DECLARE_REGISTER_TYPE_INSTRUCTION(And);
	DECLARE_IMMEDIATE_TYPE_INSTRUCTION(andi);
	DECLARE_REGISTER_TYPE_INSTRUCTION(Or);
	DECLARE_REGISTER_TYPE_INSTRUCTION(Xor);
	DECLARE_REGISTER_TYPE_INSTRUCTION(add);
	DECLARE_REGISTER_TYPE_INSTRUCTION(addu);
	DECLARE_REGISTER_TYPE_INSTRUCTION(sub);
	DECLARE_REGISTER_TYPE_INSTRUCTION(subu);
	Instr mult(uint rs, uint rt);
	Instr multu(uint rs, uint rt);
	Instr div(uint rs, uint rt);
	Instr divu(uint rs, uint rt);
	Instr nor(uint rd, uint rs, uint rt);
	Instr sll(uint rd, uint rt, uint sa);
	Instr sllv(uint rd, uint rt, uint rs);
	Instr slt(uint rd, uint rt, uint rs);

#define DECLARE_TARGET_SOURCE_IMMEDIATE_INSTRUCTION(name) \
	Instr name(uint rt, uint rs, uint imm)

	DECLARE_TARGET_SOURCE_IMMEDIATE_INSTRUCTION(slti);
	DECLARE_TARGET_SOURCE_IMMEDIATE_INSTRUCTION(sltiu);
	DECLARE_TARGET_SOURCE_IMMEDIATE_INSTRUCTION(ori);
	DECLARE_TARGET_SOURCE_IMMEDIATE_INSTRUCTION(xori);

	Instr sltu(uint rd, uint rt, uint rs);
	Instr srav(uint rd, uint rt, uint rs);
	Instr srlv(uint rd, uint rt, uint rs);

	Instr sra(uint rd, uint rt, uint sa);
	Instr srl(uint rd, uint rt, uint sa);

	Instr swc1(uint ft, uint offset, uint base);

	Instr teq(uint rs, uint rt);
	Instr tge(uint rs, uint rt);
	Instr tgeu(uint rs, uint rt);
	Instr tlt(uint rs, uint rt);

	Instr teqi(uint rs, uint imm);
	Instr tgei(uint rs, uint imm);
	Instr tgeiu(uint rs, uint imm);
}
