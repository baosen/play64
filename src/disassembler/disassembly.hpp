#pragma once
#include "../data_types/types.hpp"
#include <vector>
#include <string>

namespace disasm {
	struct Instr {
		Instr(const std::string& hex, const std::string& text)
			: hex(hex), text(text)
		{}
		std::string hex, text;
	};
}

struct Disassembly {
	const u32 entry_point;
	std::vector<disasm::Instr> instructions;
};