#include <sstream>
#include <iomanip>
#include "hex_address_stream.hpp"
#include "hex.hpp"

void Hex_addr_stream::operator<<(const uint32_t address) 
{
	clear_stream(stream);
	hexify(stream);
    stream << address;
}

Hex_addr_stream::Hex_addr_stream()
{
	stream << std::hex << std::setfill('0') << std::setw(8); // 8 bytes in an address.
}

std::string Hex_addr_stream::str()
{
	return stream.str();
}

void Hex_addr_stream::clear_stream(std::stringstream& stream)
{
	stream.str("");
}
