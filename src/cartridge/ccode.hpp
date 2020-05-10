#pragma once

// TODO: The PAL-values needs to be checked by testing out Brazilian roms.
// The Country Code stored in the Game Pak to identify the Game Pak's region that it was targeted for.
enum class country_code {
    Beta      = 0x37,
    NTSC      = 0x41,
	Germany   = 0x44, // ASCII 'D'
	USA       = 0x45, // ASCII 'E'
    France    = 0x46,
    Italy     = 0x49,
	Japan     = 0x4A, // ASCII 'J'
	Europe    = 0x50, // ASCII 'P'
    Spain     = 0x53,
	Australia = 0x55, // ASCII 'U'
    PAL       = 0x58, // Used in Europe.
    PAL_M     = 0x59, // Used in Brazil.
};