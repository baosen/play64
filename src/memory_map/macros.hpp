#pragma once

#define OFFSET instr.offset()
#define BASE   instr.base()
#define VADDR  get64(instr.base()) + sext16(instr.offset())
