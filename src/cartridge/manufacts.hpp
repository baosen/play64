#pragma once
#include "ccode.hpp"

// Assuming Nintendo uses 2 different codes for their manufacturing ids.
enum Manufacturer_id {
	Nintendo1 = 0x43,// ASCII 'N'.
	Nintendo2 = 0x4e // ASCII 'C'.
};

// An ID to define the type of cartridge I guess?
enum Cartridge_id {
	SM = 0x4d53,
};

// Returns a C-string containing the cartridge name.
const char* convert_cartridge_name_to_string(const Cartridge_id);

// Returns a C-string containing the name of the country defined by the given country code.
const char* convert_country_code_to_string(const country_code);

// Returns a C-string containing the name of the manufacturer defined by the given manufacturer id.
const char* convert_manufacture_code_to_manufacturer_string(const Manufacturer_id);