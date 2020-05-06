#include "manufacts.hpp"

const char* convert_cartridge_name_to_string(const Cartridge_id cartridge_id) {
	switch (cartridge_id) {
	case Cartridge_id::SM:
		return "SM";
	default:
		return "Unknown";
	}
}

const char* convert_country_code_to_string(const country_code country_code) {
	switch (country_code) {
	case country_code::Beta:
		return "Beta";
	case country_code::NTSC:
		return "NTSC";
	case country_code::Germany:
		return "Germany";
	case country_code::USA:
		return "United States of America";
	case country_code::France:
		return "France";
	case country_code::Italy:
		return "Italy";
	case country_code::Japan:
		return "Japan";
	case country_code::Europe:
		return "Europe";
	case country_code::Spain:
		return "Spain";
	case country_code::Australia:
		return "Australia";
	case country_code::PAL: case country_code::PAL_M:
		return "PA";
	default:
		return "Unknown";
	}
}

const char* convert_manufacture_code_to_manufacturer_string(const Manufacturer_id manufacturer_id) {
	switch (manufacturer_id) {
	case Manufacturer_id::Nintendo1: case Manufacturer_id::Nintendo2:
		return "Nintendo";
	default:
		return "Unknown";
	}
}
