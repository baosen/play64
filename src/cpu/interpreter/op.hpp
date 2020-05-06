#pragma once

enum Opcode {
	NOP = 0,
	J = 2, JAL = 3, BEQ = 4, BNE = 5, BLEZ = 6, BGTZ = 7,
	ADDI = 8, ADDIU = 9, SLTI = 10, SLTIU = 11, ANDI = 12,
	ORI = 13, XORI = 14, LUI = 15, BEQL = 20, BNEL = 21,
	BLEZL = 22, BGTZL = 23, DADDI = 24, DADDIU = 25, LDL = 26,
	LDR = 27, LB = 32, LH = 33, LWL = 34, LW = 35, LBU = 36,
	LHU = 37, LWR = 38, LWU = 39, SB = 40, SH = 41, SWL = 42,
	SW = 43, SDL = 44, SDR = 45, SWR = 46, LL = 48, LWC1 = 49,
	LWC2 = 50, LLD = 52, LDC1 = 53, LDC2 = 54, LD = 55, SC = 56,
	SWC1 = 57, SWC2 = 58, SCD = 60, SDC1 = 61, SDC2 = 62, SD = 63,
};