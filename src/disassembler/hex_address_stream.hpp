#pragma once
#include <sstream>
#include "../data_types/types.hpp"

class Hex_addr_stream {
public:
	Hex_addr_stream();
	void operator<<(const u32 address);
	std::string str();
private:
	// Clear the buffer inside the stream to build a new string.
	void clear_stream(std::stringstream& stream);

	std::stringstream stream;
};