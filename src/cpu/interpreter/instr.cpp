#include "instr.hpp"
#include "op.hpp"
#include "bitpos.hpp"
using namespace std;

Instr::Instr(const u32 i) : instr(i) {}

uint Instr::rd() const {
	return (instr & 0xF800) >> DEST_POS;
}

uint Instr::rs() const {
	return (instr & 0x3e00000) >> SRC_POS;
}

uint Instr::rt() const {
	return (instr & 0x1F0000) >> TARGET_POS;
}

int Instr::imm() const {
	return instr & 0xFFFF;
}

bool Instr::is_special() const {
	return (instr & INSTRUCTION_MASK) == 0;
}

Special_opcode Instr::special() const {
	return static_cast<Special_opcode>(instr & 0x3F);
}

uint Instr::spec() const {
	return instr & 0x3F;
}

Opcode Instr::normal() const {
	return static_cast<Opcode>((instr & INSTRUCTION_MASK) >> OPCODE_POS);
}

bool Instr::is_regimm() const {
	return (instr & INSTRUCTION_MASK) == 0x4000000;
}

bool Instr::is_cop0() const {
	return (instr & INSTRUCTION_MASK) == 0x40000000;
}

bool Instr::is_cop1() const {
	return (instr & INSTRUCTION_MASK) == 0x44000000;
}

bool Instr::is_cop2() const {
	return (instr & INSTRUCTION_MASK) == 0x48000000;
}

bool Instr::is_nop() const {
	return (instr & 0xFFFFFFFF) == NOP;
}

uint Instr::base() const {
	return (instr & 0x3e00000) >> 21;
}

int Instr::offset() const {
	return instr & 0xFFFF;
}

uint Instr::instr_idx() const {
	return instr & 0x3FFFFFF;
}

uint Instr::sa() const {
	return (instr & 0x7C0) >> 6;
}

Regimms Instr::regimm() const {
	return static_cast<Regimms>((instr & 0x1F0000) >> 16);
}

uint Instr::cop0() const {
	return (instr >> 21) & 0x1f;
}

uint Instr::tlb() const {
	return instr & 0x1F;
}

Instr::operator u32() const {
	return instr;
}

ostream& operator<<(ostream& o, const Instr i) {
	o << i.instr;
	return o;
}

wostream& operator<<(wostream& wo, const Instr i) {
	wo << i.instr;
	return wo;
}

bool operator==(const Instr& i, const u32 value) {
	return i.instr == value;
}

bool operator==(const u32 val, const Instr& i) {
	return operator==(i, val);
}
