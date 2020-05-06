#pragma once

// Official assembly-names for registers:
enum Register {
	zero = 0, // always zero.
	at, // reserved for assembler.
	v0, v1, // stores results.
	a0, a1, a2, a3, // stores arguments.
	t0, t1, t2, t3, t4, t5, t6, t7, // temporaries, not saved.
	s0, s1, s2, s3, s4, s5, s6, s7, // contents saved for use later.
	t8, t9, // more temporaries, not saved.
	k0, k1, // reserved by the operating system.
	gp, // global pointer.
	sp, // stack pointer.
	fp, // frame pointer.
	ra, // contains the return address.
};