/*
#include <sstream>
using namespace std;
#include "pak.hpp"
#include "bswap.hpp"
#include "manufacts.hpp"
#include "mem.hpp"
#include "head.hpp"

namespace {
    // Empty the given string-stream.
    void clear(stringstream& wss) { wss.str(""); }

    // Print to the log.
    void print_to_log(stringstream& wss) { ::log(wss.str().c_str(), "[ROM]"); }
}

// Byteswap the bytes to the correct endianness that Nintendo 64 uses.
void Rom_header::bswap() {
    rombswap(this, sizeof(*this));
}

// Initialize an empty Game Pak ROM header.
Rom_header::Rom_header() {
    memzero(this, sizeof(*this));
}

// Load the ROM header from the Game Pak's ROM memory.
Rom_header::Rom_header(Pak& pak) {
    pak.copy(this, sizeof(Rom_header));
    bswap();
}

// Output rom header info to the log.
void Rom_header::log() {
    stringstream wss;
    wss << "Clock rate: " << clock_rate;
    print_to_log(wss);
    clear(wss);
    wss << "Entry-point: " << hex << showbase << program_counter;
    print_to_log(wss);
	clear(wss);
	wss << "Release: " << hex << showbase << release;
	print_to_log(wss);
	clear(wss);
	wss << "CRC1: " << hex << showbase << crc1;
	print_to_log(wss);
	clear(wss);
	wss << "CRC2: " << hex << showbase << crc2;
	print_to_log(wss);
	clear(wss);
	bswap_words(reinterpret_cast<uint32_t*>(cartridge_name), 5);
	wss << "Image name: " << cartridge_name;
	print_to_log(wss);
	clear(wss);
	wss << "Manufacturer ID: " << hex << showbase << manufacturer_id << " (" << convert_manufacture_code_to_manufacturer_string(static_cast<Manufacturer_id>(manufacturer_id)) << ')';
	print_to_log(wss);
	clear(wss);
	auto cart = bswap16(cartridge_id);
	wss << "Cartridge ID: " << hex << showbase << cart << " (" << convert_cartridge_name_to_string(static_cast<Cartridge_id>(cart)) << dec << ")";
	print_to_log(wss);
	clear(wss);
	auto country = bswap16(country_code);
	wss << "Country code: " << hex << showbase << country << dec << " (" << convert_country_code_to_string(static_cast<Ccode>(country)) << ')';
	print_to_log(wss);
}

// Returns the program-counter/entry-point of the ROM.
uint32_t Rom_header::get_entry_point() const {
	return program_counter;
}
*/
