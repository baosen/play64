#pragma once

#define CHECK_PC CHECK_EQUAL(GAME_CODE_START, i.pc());

#define DEF_INTERP(name) \
	Interp name; \
	name.fakeload(); \
	CHECK_PC

#define STEP_ONCE(fn) \
	DEF_INTERP(i) \
	i[GAME_CODE_START] = (fn); \
	i.step();

#define SET_CHECK(reg, val) \
	i.set64(reg, val); \
	CHECK_EQUAL(i.get64(reg), val)

#define SET_INSTR(fn) \
	DEF_INTERP(i) \
	i[GAME_CODE_START] = (fn); \
	i[GAME_CODE_START+4] = NOP;