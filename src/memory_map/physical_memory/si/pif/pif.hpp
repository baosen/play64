#pragma once
/**********************************************************
 * PIF Physical memory map (total size = 2 KB)
 *
 *				  Size	    Description     Mode
 *	1FC007FF	+-------+-----------------+-----+
 *			    |  64 B | JoyChannel RAM  | R/W |
 *	1FC007C0	+-------+-----------------+-----+
 *			    |1984 B |    Boot ROM     |  *  |  * = Reserved
 *	1FC00000	+-------+-----------------+-----+
 **/

// At 0x1FC0 07C4-07c5 is the status of the controller, each bit is 1 when the button is mashed, 0 otherwise.
// 07C4 (HALFWORD - 16 BITS) = STATUS OF CONTROLLER
//  %X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X
//   A  B  Z  ST U  D  L  R ? ? PL PR CU CD CL CR
// A, B, Z = BUTTONS
// ST = START
// U, D, L, R = JOYPAD
// ? , ? = UNKNOWN
// PL, PR = PAN LEFT, PAN RIGHT BUTTONS
// CU, CD, CL, CR = C BUTTONS | UP, DOWN, LEFT, RIGHT

enum {
	BOOT_ROM_START  = 0x1FC00000,
	BOOT_ROM_END    = 0x1FC007BF,
// 1984 bytes long.
	JOYCHANNEL_RAM_START = 0x1FC007C0,
	JOYCHANNEL_RAM_END   = 0x1FC007FF,
// 64 bytes long.
};
