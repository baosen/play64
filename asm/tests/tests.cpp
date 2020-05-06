#include <assembler.hpp>
using namespace assembler;

#include "op.hpp"
#include "specials.hpp"
#include "regimms.hpp"
#include <instr/bitpos.hpp>

#include <UnitTest++.h>

// TODO: 
// - Implement error-checks for setting a register that does not exist (larger than 31).
// - Mask all opcodes with 6-bits (0x3f).
// - Test all register- and address-combinations (makes tests run slooooow...).

#define CAST_UINT(expr) static_cast<unsigned int>(expr)

// 153 instructions in total.
SUITE(assem) {
	TEST(shiftamt) {
		CHECK_EQUAL(3 << 6, shiftamt(3));
	}
	TEST(base) {
		CHECK_EQUAL(3 << (5 + 16), base(3));
	}
	TEST(hint) {
		CHECK_EQUAL(3 << 6, hint(3));
	}
	TEST(offset) {
		CHECK_EQUAL(0xffff, offset(0xffffffff));
	}
	TEST(instr_idx) {
		for (uint32_t addr(0); addr < 0x3ffffff; ++addr)
			CHECK_EQUAL(addr, instr_idx(addr | 0xf0000000));
	}
	TEST(opcode) { 
		CHECK_EQUAL(J << OPCODE_POS, opcode(J)); 
	}
	TEST(add) { 
		CHECK_EQUAL(0x211020, add(2, 1, 1)); 
	}
	TEST(addi) { 
		CHECK_EQUAL(0x20210001, addi(1, 1, 1));
	}
	TEST(addiu) { 
		CHECK_EQUAL(0x24210001, addiu(1, 1, 1)); 
	}
	TEST(addu) { 
		CHECK_EQUAL(0x210821, addu(1, 1, 1)); 
	}
	TEST(And) { 
		CHECK_EQUAL(0x210824, And(1, 1, 1)); 
	}
	TEST(andi) { 
		CHECK_EQUAL(0x30210002, andi(1, 1, 2)); 
	}
	TEST(beq) { 
		CHECK_EQUAL(0x10210002, beq(1, 1, 2)); 
	}
	TEST(beql) { 
		CHECK_EQUAL(0x50210002, beql(1, 1, 2)); 
	}
	TEST(bgez) { 
		CHECK_EQUAL(regimm(BGEZ) | source(1) | offset(0xbeef), bgez(1, 0xbeef));
	}
	TEST(bgezal) {
		CHECK_EQUAL(regimm(BGEZAL) | source(1) | offset(0xdead), bgezal(1, 0xdead));
	}
	TEST(bgezall) {
		CHECK_EQUAL(regimm(BGEZALL) | source(3) | offset(0xbabe), bgezall(3, 0xbabe));
	}
	TEST(bgezl) {
		CHECK_EQUAL(regimm(BGEZL) | source(10) | offset(0xdeed), bgezl(10, 0xdeed));
	}
	TEST(bgtz) {
		CHECK_EQUAL(opcode(BGTZ) | source(3) | offset(0xbeef), bgtz(3, 0xbeef));
	}
	TEST(bgtzl) {
		CHECK_EQUAL(opcode(BGTZL) | source(3) | offset(0xbeef), bgtzl(3, 0xbeef));
	}
	TEST(blez) {
		CHECK_EQUAL(opcode(BLEZ) | source(12) | offset(0x1234), blez(12, 0x1234));
	}
	TEST(blezl) {
		CHECK_EQUAL(opcode(BLEZL) | source(12) | offset(0x1234), blezl(12, 0x1234));
	}
	TEST(bltz) {
		CHECK_EQUAL(regimm(BLTZ) | source(9) | offset(300), bltz(9, 300));
	}
	TEST(bltzal) {
		CHECK_EQUAL(regimm(BLTZAL) | source(9) | offset(300), bltzal(9, 300));
	}
	TEST(bltzall) {
		CHECK_EQUAL(regimm(BLTZALL) | source(9) | offset(300), bltzall(9, 300));
	}
	TEST(bltzl) {
		CHECK_EQUAL(regimm(BLTZL) | source(9) | offset(300), bltzl(9, 300));
	}
	TEST(bne) { 
		CHECK_EQUAL(0x14210003, bne(1, 1, 3)); 
	}
	TEST(bnel) { 
		CHECK_EQUAL(0x54210004, bnel(1, 1, 4)); 
	}
	TEST(div) {
		CHECK_EQUAL(source(2) | target(4) | CAST_UINT(Special_opcode::DIV), assembler::div(2, 4));
	}
	TEST(divu) {
		CHECK_EQUAL(source(2) | target(4) | CAST_UINT(Special_opcode::DIVU), assembler::divu(2, 4));
	}
	TEST(j) {
// TODO: Test all addresses (which may execute too slowly).
		for (uint32_t addr(0); addr < 0xffff; ++addr) 
			CHECK_EQUAL(0x08000000 | addr, j(addr));
	}
	TEST(jal) { 
		CHECK_EQUAL(0x0C000000 | 0x1000, jal(0x1000)); 
	}
	TEST(jalr) { 
		CHECK_EQUAL(dest(2) | source(1) | (CAST_UINT(Special_opcode::JALR) & 0x3f), jalr(2, 1)); 
	}
	TEST(jr) {
		CHECK_EQUAL(source(3) | CAST_UINT(Special_opcode::JR), jr(3));
	}
	TEST(lb) {
		CHECK_EQUAL(opcode(LB) | base(4) | target(2) | offset(0xbeef), lb(2, 0xbeef, 4));
	}
	TEST(lbu) {
		CHECK_EQUAL(opcode(LBU) | base(6) | target(9) | offset(0xbaba), lbu(9, 0xbaba, 6));
	}
	TEST(lh) {
		CHECK_EQUAL(opcode(LH) | base(6) | target(9) | offset(0xbaba), lh(9, 0xbaba, 6));
	}
	TEST(lhu) {
		CHECK_EQUAL(opcode(LHU) | base(6) | target(9) | offset(0xbaba), lhu(9, 0xbaba, 6));
	}
	TEST(ll) {
		CHECK_EQUAL(opcode(LL) | base(6) | target(9) | offset(0xbaba), ll(9, 0xbaba, 6));
	}
	TEST(lui) {
		CHECK_EQUAL(opcode(LUI) | target(10) | immediate(4521), lui(10, 4521));
	}
	TEST(lw) {
		CHECK_EQUAL(opcode(LW) | base(2) | target(22) | offset(23), lw(22, 23, 2));
	}
	TEST(lwl) {
		CHECK_EQUAL(opcode(LWL) | base(1) | target(1) | offset(1), lwl(1, 1, 1));
	}
	TEST(lwr) {
		CHECK_EQUAL(opcode(LWR) | base(1) | target(1) | offset(1), lwr(1, 1, 1));
	}
	TEST(mfhi) {
		CHECK_EQUAL(dest(12) | CAST_UINT(Special_opcode::MFHI), mfhi(12));
	}
	TEST(mflo) {
		CHECK_EQUAL(dest(12) | CAST_UINT(Special_opcode::MFLO), mflo(12));
	}
	TEST(mthi) {
		CHECK_EQUAL(source(22) | CAST_UINT(Special_opcode::MTHI), mthi(22));
	}
	TEST(mtlo) {
		CHECK_EQUAL(source(22) | CAST_UINT(Special_opcode::MTLO), mtlo(22));
	}
	TEST(mult) {
		CHECK_EQUAL(source(2) | target(4) | CAST_UINT(Special_opcode::MULT), mult(2, 4));
	}
	TEST(multu) {
		CHECK_EQUAL(source(1) | target(6) | CAST_UINT(Special_opcode::MULTU), multu(1, 6)); 
	}
	TEST(nop) { 
		CHECK_EQUAL(0, nop()); 
	}
	TEST(nor) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::NOR), nor(1, 1, 1));
	}
	TEST(Or) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::OR), Or(1,1,1));
	}
	TEST(ori) {
		CHECK_EQUAL(opcode(ORI) | source(1) | target(1) | immediate(1), ori(1,1,1));
	}
	TEST(sb) {
		CHECK_EQUAL(opcode(SB) | base(1) | target(1) | offset(1), sb(1, 1, 1));
	}
	TEST(sc) {
		CHECK_EQUAL(opcode(SC) | base(1) | target(1) | offset(1), sc(1, 1, 1));
	}
	TEST(sh) {
		CHECK_EQUAL(opcode(SH) | base(1) | target(1) | offset(1), sh(1, 1, 1));
	}
	TEST(sll) {
		CHECK_EQUAL(target(1) | dest(1) | shiftamt(1) | CAST_UINT(Special_opcode::SHIFT_WORD_LEFT_LOGICAL), sll(1, 1, 1));
	}
	TEST(sllv) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::SLLV), sllv(1, 1, 1));
	}
	TEST(slt) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::SLT), slt(1, 1, 1));
	}
	TEST(slti) {
		CHECK_EQUAL(opcode(SLTI) | source(2) | target(2) | immediate(123), slti(2, 2, 123));
	}
	TEST(sltiu) {
		CHECK_EQUAL(opcode(SLTIU) | source(2) | target(2) | immediate(123), sltiu(2, 2, 123));
	}
	TEST(sltu) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::SLTU), sltu(1, 1, 1));
	}
	TEST(sra) {
		CHECK_EQUAL(target(1) | dest(1) | shiftamt(1) | CAST_UINT(Special_opcode::SRA), sra(1,1,1));
	}
	TEST(srav) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::SRAV), srav(1, 1, 1));
	}
	TEST(srl) {
		CHECK_EQUAL(target(1) | dest(1) | shiftamt(1) | CAST_UINT(Special_opcode::SRL), srl(1, 1, 1));
	}
	TEST(srlv) {
		CHECK_EQUAL(source(1) | target(1) | dest(1) | CAST_UINT(Special_opcode::SRLV), srlv(1, 1, 1));
	}
	TEST(sub) { 
		CHECK_EQUAL(0x210822, sub(1, 1, 1)); 
	}
	TEST(subu) { 
		CHECK_EQUAL(0x210823, subu(1, 1, 1)); 
	}
	TEST(sw) {
		CHECK_EQUAL(opcode(SW) | base(1) | target(1) | offset(1), sw(1, 1, 1));
	}
	TEST(swc1) {
		CHECK_EQUAL(opcode(SWC1) | base(1) | target(1) | offset(1), swc1(1, 1, 1));
	}
	TEST(swc2) {
		CHECK_EQUAL(opcode(SWC2) | base(1) | target(1) | offset(1), swc2(1, 1, 1));
	}
	TEST(swl) {
		CHECK_EQUAL(opcode(SWL) | base(1) | target(1) | offset(1), swl(1, 1, 1));
	}
	TEST(swr) {
		CHECK_EQUAL(opcode(SWR) | base(1) | target(1) | offset(1), swr(1, 1, 1));
	}
	TEST(teq) {
		CHECK_EQUAL(source(1) | target(1) | CAST_UINT(Special_opcode::TEQ), teq(1, 1));
	}
	TEST(teqi) {
		CHECK_EQUAL(source(1) | regimm(TEQI) | immediate(1), teqi(1, 1));
	}
	TEST(tge) {
		CHECK_EQUAL(source(1) | target(1) | CAST_UINT(Special_opcode::TGE), tge(1, 1));
	}
	TEST(tgei) {
		CHECK_EQUAL(source(1) | regimm(TGEI) | immediate(1), tgei(1, 1));
	}
	TEST(tgeiu) {
		CHECK_EQUAL(source(1) | regimm(TGEIU) | immediate(1), tgeiu(1, 1));
	}
	TEST(tgeu) {
		CHECK_EQUAL(source(1) | target(1) | CAST_UINT(Special_opcode::TGEU), tgeu(1, 1));
	}
	TEST(tlt) {
		CHECK_EQUAL(source(1) | target(1) | CAST_UINT(Special_opcode::TLT), tlt(1, 1));
	}
	TEST(Xor) { 
		CHECK_EQUAL(0x210826, Xor(1, 1, 1)); 
	}
	TEST(xori) {
		CHECK_EQUAL(opcode(XORI) | source(1) | target(1) | immediate(1), xori(1, 1, 1));
	}
}

int main() { 
	return UnitTest::RunAllTests(); 
}