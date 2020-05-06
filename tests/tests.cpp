// TODO: 
// - Test binary-string builders.
// - Test all register-combinations.
// - Setting register 0 to some other illegal value. Should not do anything. Reg 0 ($zero) is always 0!
// - Test error-cases.
// - Test negative add, addu, addiu bla bla... same with positive sub.
#include "macros.hpp"
#include <interp/interp.hpp>
#include "op.hpp"
#include <instr/bitpos.hpp>
#include <asm/asm.hpp>
using namespace assem;
#include <UnitTest++.h>
#include <windows.h>

SUITE(interp) {
// Test registers:
	TEST(gpr0) {
// Set GPR[0] to 1, which should fail.
		DEF_INTERP(i)
		i.set64(0, 1);
		CHECK_EQUAL(0, i.get64(0));
	}
// TODO: Implement exception.
	TEST(add) {
		SET_INSTR(add(3, 2, 1))
		CHECK_EQUAL(add(3, 2, 1), i[GAME_CODE_START]);
		CHECK_EQUAL(0, i.get64(0));
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 2);
		i.set64(1, 1);
		i.step();
		CHECK_EQUAL(3, i.get64(3));
	}
// TODO: Implement SignalException(IntegerOverflow)
	TEST(addi) {
		SET_INSTR(addi(3, 2, 10));
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 4);
		CHECK_EQUAL(4, i.get64(2));
		i.step();
		CHECK_EQUAL(14, i.get64(3));
	}
	TEST(addiu) {
		SET_INSTR(addiu(3, 2, 20));
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 10);
		CHECK_EQUAL(10, i.get64(2));
		i.step();
		CHECK_EQUAL(30, i.get64(3));
	}
	TEST(addu) {
		SET_INSTR(addu(3, 2, 1))
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 2);
		i.set64(1, 1);
		i.step();
		CHECK_EQUAL(3, i.get64(3));
	}
	TEST(And) {
		SET_INSTR(And(1, 1, 1))
		i.set64(1, 1);
		i.step();
		CHECK_EQUAL(1, i.get64(1));
	}
	TEST(andi) {
		SET_INSTR(andi(5, 6, 1))
		i.set64(6, 1);
		CHECK_EQUAL(1, i.get64(6));
		i.step();
		CHECK_EQUAL(1, i.get64(5));
	}

// TODO: Test for correct delay slot-execution.
	TEST(beq) {
		SET_INSTR(beq(1, 2, 2))
		SET_CHECK(1, 3);
		SET_CHECK(2, 3);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(beql) {
		SET_INSTR(beql(1, 2, 2))
		i.set64(1, 1);
		CHECK_EQUAL(i.get64(1), 1);
		i.set64(2, 1);
		CHECK_EQUAL(i.get64(2), 1);
		auto before(i.pc());
		i.step();
		CHECK_EQUAL(i.pc(), before + INSTR_SIZE + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bgez) {
		SET_INSTR(bgez(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bgezal) {
		SET_INSTR(bgezal(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(d + (2 << 2), i.pc());
		CHECK_EQUAL(d + 4, i.get64(31)); // link.
		// TODO: Test false-condition.
	}
	TEST(bgezall) {
		SET_INSTR(bgezall(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(d + (2 << 2), i.pc());
		CHECK_EQUAL(d + 4, i.get64(31)); // link.
		// TODO: Test false-condition.
	}
	TEST(bgezl) {
		SET_INSTR(bgezl(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bgtz) {
		SET_INSTR(bgtz(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + 2*INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bgtzl) {
		SET_INSTR(bgtzl(1, 2))
		SET_CHECK(1, 1);
		auto d(i.pc() + 2*INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(blez) {
		SET_INSTR(blez(1, 2))
		SET_CHECK(1, 0);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(blezl) {
		SET_INSTR(blezl(1, 2))
		SET_CHECK(1, 0);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bltz) {
		SET_INSTR(bltz(1, 2))
		SET_CHECK(1, -1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bltzal) {
		SET_INSTR(bltzal(1, 2))
		SET_CHECK(1, -1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		CHECK_EQUAL(d + 4, i.get64(31)); // link.
		// TODO: Test false-condition.
	}
	TEST(bltzall) {
		SET_INSTR(bltzall(1, 2))
		SET_CHECK(1, -1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		CHECK_EQUAL(d + 4, i.get64(31)); // link.
		// TODO: Test false-condition.
	}
	TEST(bltzl) {
		SET_INSTR(bltzl(1, 2))
		SET_CHECK(1, -1);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
		// TODO: Test false-condition.
	}
	TEST(bne) {
		SET_INSTR(bne(1, 2, 2))
		SET_CHECK(1, 1);
		SET_CHECK(1, 2);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
	}
	TEST(bnel) {
		SET_INSTR(bnel(1, 2, 2))
		SET_CHECK(1, 1);
		SET_CHECK(1, 2);
		auto d(i.pc() + INSTR_SIZE);
		i.step();
		CHECK_EQUAL(i.pc(), d + (2 << 2));
	}
	TEST(div) {
	}
	TEST(divu) {
	}
	TEST(j) {
		SET_INSTR(j(10));
		auto d(i.pc() + INSTR_SIZE); // branch delay slot.
		i.step();
		CHECK_EQUAL((d & 0xf8000000) | (10 << 2), i.pc());
	}
	TEST(jal) {
		SET_INSTR(jal(0x1000))
		auto d(i.pc());
		i.step();
		CHECK_EQUAL(d+8, i.get64(31));
	}
	TEST(nop) {
		STEP_ONCE(NOP)
		CHECK_EQUAL(GAME_CODE_START + 4, i.pc());
	}
	TEST(Or) {
		SET_INSTR(Or(3, 2, 1))
		i.set64(2, 1);
		i.set64(1, 0);
		i.step();
		CHECK_EQUAL(1, i.get64(2));
	}
	TEST(ori) {
		SET_INSTR(ori(2, 1, 2))
		SET_CHECK(1, 1);
		SET_CHECK(2, 10);
		i.step();
		CHECK_EQUAL(i.get64(2), 3);
	}
	TEST(sw) {
		SET_INSTR(sw(3, 4, 4))
		SET_CHECK(4, 0x80000000);
		SET_CHECK(3, 1);
		i.step();
		CHECK_EQUAL(i[0x80000004], 1);
	}
	TEST(sb) {
		SET_INSTR(sb(1, 2, 3));
		SET_CHECK(3, 3);
	}
// TODO: Implement exception.
	TEST(sub) {
		SET_INSTR(sub(3, 2, 1))
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 3);
		i.set64(1, 2);
		i.step();
		CHECK_EQUAL(1, i.get64(3));
	}
	TEST(subu) {
		SET_INSTR(subu(3, 2, 1))
		i.set64(3, 0);
		CHECK_EQUAL(0, i.get64(3));
		i.set64(2, 3);
		i.set64(1, 2);
		i.step();
		CHECK_EQUAL(1, i.get64(3));
	}
	TEST(Xor) {
		SET_INSTR(Xor(3, 2, 1))
		i.set64(2, 1);
		i.set64(1, 1);
		i.step();
		CHECK_EQUAL(0, i.get64(3));
	}
}

int main() { return UnitTest::RunAllTests(); }