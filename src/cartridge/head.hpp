#pragma once

struct Head {
	u8 header_bytes[4];	 // Magic header numbers that indicate it is a ROM from a Nintendo 64 cartridge.  
	// The third byte 0x2 is set to either 12h if the ROM is uncompressed, or 13h if ROM is compressed (RTool standard).
	u32 clock_rate; // Initial clock-rate.
	u32 program_counter; // The ROM's entry point. This is the address to load the ROM. Game code most of the time starts at offset 0x1000.
	u32 release; // Release offset.
	u32 crc1; // First CRC verification checksum.
	u32 crc2; // Second CRC verification checksum.
	u32 unused[2]; // Unused.
	char cartridge_name[20]; // Name of the game on the game cartridge.
	u32 unused_2; // Unused.
	u32 manufacturer_id; // The ID of the manufacturer. Often 0x4e, which is the ID for Nintendo.
	u16 country_code; // The code for the country the game was aimed to sell in.
	u16 cartridge_id; // An unique ID for the cartridge.
};

class Pak;

class Rom_header : private Head {
public:	
	// Initialize an empty ROM header.
    Rom_header();

    // Reads the ROM header from a Game Pak (ROM) loaded into the memory.
    Rom_header(Pak& pak);

	// Print out the header in the log.
	void log();

	// Returns the entry-point of the ROM read from the ROM's header.
    u32 get_entry_point() const;
private:
	void bswap();
};
