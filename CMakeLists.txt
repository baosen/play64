cmake_minimum_required(VERSION 3.16.3)
project(play64)

# Set to use C++20.
set(CMAKE_CXX_STANDARD 20)

# Import OpenGL.
find_package(OpenGL REQUIRED)

# Import WxWidgets.
find_package(wxWidgets COMPONENTS core base aui gl REQUIRED)
include(${wxWidgets_USE_FILE})

set(SRC
        src/memory_map/physical_memory/ai/ai.cpp
        src/memory_map/physical_memory/ai/ai.hpp
        src/aligned.hpp
        src/gui/app.cpp
        src/cli/args.cpp
        src/cli/args.hpp
        src/cpu/interpreter/bitpos.hpp
        src/memory_map/byteswap.cpp
        src/memory_map/byteswap.hpp
        src/cartridge/ccode.hpp
        src/memory_map/physical_memory/si/pif/cic.cpp
        src/gui/cmd.hpp
        src/cli/cmdparams.cpp
        src/cli/cmdparams.hpp
        src/cpu/cop0/cop0.cpp
        src/cpu/cop0/cop0const.hpp
        src/cpu/cop0/cop0str.cpp
        src/cpu/cop0/cop0str.hpp
        src/cpu/cop1/cop1.cpp
        src/cpu/cop1/cop1str.cpp
        src/cpu/cop1/cop1str.hpp
        src/cpu/interpreter/registers/cpu.cpp
        src/cpu/interpreter/registers/cpu.hpp
        src/cli/cstr.cpp
        src/cli/cstr.hpp
        src/cpu/cop0/syscon.cpp
        src/cpu/cop0/syscon.hpp
        src/gui/dbg.cpp
        src/gui/dbg.hpp
        src/cli/debug.cpp
        src/cli/debug.hpp
        src/disassembler/decode.cpp
        src/disassembler/decode.hpp
        src/gui/disasm.cpp
        src/gui/disasm.hpp
        src/disassembler/disassembly.hpp
        src/gui/dlg.cpp
        src/gui/dlg.hpp
        src/cpu/interpreter/err.hpp
        src/cpu/fpu/fpu.cpp
        src/cpu/fpu/fpu.hpp
        src/gui/frames/main_frame.cpp
        src/gui/frames/main_frame.hpp
        src/head.cpp
        src/head.hpp
        src/disassembler/hex.cpp
        src/disassembler/hex.hpp
        src/disassembler/hex_address_stream.cpp
        src/disassembler/hex_address_stream.hpp
        src/gui/id.hpp
        src/cpu/interpreter/instr.cpp
        src/cpu/interpreter/instr.hpp
        src/cpu/interpreter/instrstr.hpp
        src/cpu/interpreter/instrsz.hpp
        src/cpu/interpreter/interp.cpp
        src/cpu/interpreter/interp.hpp
        src/cartridge/manufacts.cpp
        src/cartridge/manufacts.hpp
        src/memory_map/mem.cpp
        src/memory_map/mem.hpp
        src/memory_map/memaddr.hpp
        src/memory_map/memmacros.hpp
        src/gui/menu.cpp
        src/gui/menu.hpp
        src/memory_map/physical_memory/mi/mi.cpp
        src/memory_map/physical_memory/mi/mi.hpp
        src/cpu/interpreter/normals/normals.cpp
        src/cpu/interpreter/normals/normals.hpp
        src/cpu/interpreter/normals/normalsstr.cpp
        src/cpu/interpreter/normals/normalsstr.hpp
        src/cpu/interpreter/op.hpp
        src/memory_map/physical_memory/cart/pak.cpp
        src/memory_map/physical_memory/cart/pak.hpp
        src/cpu/interpreter/pc.hpp
        src/gui/periph.cpp
        src/gui/periph.hpp
        src/memory_map/physical_memory/physmem.cpp
        src/memory_map/physical_memory/physmem.hpp
        src/memory_map/physical_memory/pi/pi.cpp
        src/memory_map/physical_memory/pi/pi.hpp
        src/memory_map/physical_memory/si/pif/pif.cpp
        src/memory_map/physical_memory/si/pif/pif.hpp
        src/cli/printstep.cpp
        src/cli/printstep.hpp
        src/memory_map/physical_memory/rdram/rdram.cpp
        src/memory_map/physical_memory/rdram/rdram.hpp
        src/cpu/interpreter/regimms/regimms.cpp
        src/cpu/interpreter/regimms/regimmsstr.cpp
        src/cpu/interpreter/regimms/regimmsstr.hpp
        src/cpu/interpreter/registers/register.hpp
        src/gui/list_views/regs.cpp
        src/gui/list_views/regs.hpp
        src/memory_map/physical_memory/ri/ri.cpp
        src/memory_map/physical_memory/ri/ri.hpp
        src/cpu/interpreter/sext.cpp
        src/cpu/interpreter/sext.hpp
        src/memory_map/physical_memory/si/si.cpp
        src/memory_map/physical_memory/si/si.hpp
        src/signal.cpp
        src/signal.hpp
        src/memory_map/physical_memory/sp/sp.cpp
        src/memory_map/physical_memory/sp/sp.hpp
        src/cpu/interpreter/specials/specials.cpp
        src/cpu/interpreter/specials/specials.hpp
        src/cpu/interpreter/specials/specialsstr.cpp
        src/cpu/interpreter/specials/specialsstr.hpp
        src/disassembler/strings.cpp
        src/disassembler/strings.hpp
        src/cpu/strings/strmacros.hpp
        src/disassembler/strmanip.cpp
        src/disassembler/strmanip.hpp
        src/cpu/tlb/tblsize.hpp
        src/cpu/tlb/tlb.cpp
        src/cpu/tlb/tlb.hpp
        src/cpu/tlb/tlbops.cpp
        src/cpu/tlb/tlbstr.cpp
        src/disassembler/tlbstr.hpp
        src/tmem.hpp
        src/cli/trace.cpp
        src/cli/trace.hpp
        src/data_types/types.hpp
        src/memory_map/physical_memory/vi/vi.cpp
        src/memory_map/physical_memory/vi/vi.hpp
        src/gui/list_views/viview.cpp
        src/gui/list_views/viview.hpp
        src/memory_map/virtual_memory/vmem.cpp
        src/memory_map/virtual_memory/vmem.hpp
        src/memory_map/mips_exception_handlers.hpp
        src/logging/log.cpp src/logging/log.hpp src/gui/VideoOutput.h src/gui/VideoOutput.cpp)

# Compile source code and link it to an executable.
add_executable(play64 ${SRC})
target_link_libraries(play64 ${wxWidgets_LIBRARIES} ${OPENGL_LIBRARIES})
