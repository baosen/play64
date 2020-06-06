project(
    'play64!',
    'cpp',
    default_options: [
        'cpp_std=c++2a',
    ]
)

executable(
    'play64', [
    'src/gui/app.cpp',
    'src/gui/dbg.cpp',
    'src/gui/disasm.cpp',
    'src/gui/dlg.cpp',
    'src/gui/frames/main_frame.cpp',
    'src/gui/menu.cpp',
    'src/gui/periph.cpp',
    'src/gui/list_views/regs.cpp',
    'src/gui/list_views/viview.cpp',
    'src/gui/VideoOutput.cpp',
    #'src/cli/args.cpp',
    #'src/cli/cmdparams.cpp',
    #'src/cli/cstr.cpp',
    #'src/cli/debug.cpp',
    #'src/cli/printstep.cpp',
    #'src/cli/trace.cpp',
    'src/memory_map/byteswap.cpp',
    'src/memory_map/physical_memory/ai/ai.cpp',
    'src/memory_map/physical_memory/si/pif/cic/cic6105.cpp',
    'src/memory_map/physical_memory/physmem.cpp',
    'src/memory_map/physical_memory/pi/pi.cpp',
    'src/memory_map/physical_memory/si/pif/pif.cpp',
    'src/memory_map/physical_memory/rdram/rdram.cpp',
    'src/memory_map/mem.cpp',
    'src/memory_map/physical_memory/mi/mi.cpp',
    'src/memory_map/physical_memory/cart/pak.cpp',
    'src/memory_map/physical_memory/ri/ri.cpp',
    'src/memory_map/physical_memory/si/si.cpp',
    'src/memory_map/physical_memory/sp/sp.cpp',
    'src/memory_map/physical_memory/dp/dp.cpp',
    'src/memory_map/physical_memory/vi/vi.cpp',
    'src/memory_map/virtual_memory/vmem.cpp',
    'src/cpu/cop0/cop0.cpp',
    'src/cpu/cop0/cop0str.cpp',
    'src/cpu/cop1/cop1.cpp',
    'src/cpu/cop1/cop1str.cpp',
    'src/cpu/interpreter/registers/cpu.cpp',
    'src/cpu/cop0/syscon.cpp',
    'src/cpu/fpu/fpu.cpp',
    'src/cpu/interpreter/instr.cpp',
    'src/cpu/interpreter/interp.cpp',
    'src/cpu/interpreter/regimms/regimms.cpp',
    'src/cpu/interpreter/regimms/regimmsstr.cpp',
    'src/cpu/interpreter/normals/normals.cpp',
    'src/cpu/interpreter/normals/normalsstr.cpp',
    'src/cpu/interpreter/sext.cpp',
    'src/cpu/tlb/tlb.cpp',
    'src/cpu/tlb/tlbops.cpp',
    'src/cpu/tlb/tlbstr.cpp',
    'src/cpu/interpreter/specials/specials.cpp',
    'src/cpu/interpreter/specials/specialsstr.cpp',
    'src/disassembler/decode.cpp',
    'src/disassembler/hex.cpp',
    'src/disassembler/hex_address_stream.cpp',
    'src/disassembler/strings.cpp',
    'src/disassembler/strmanip.cpp',
    'src/cartridge/manufacts.cpp',
    'src/signal.cpp',
    'src/logging/log.cpp',
], dependencies: [
    dependency(
        'wxwidgets',
        version: '>=3.0.0',
        modules: ['core','base', 'aui', 'gl']
    ),
    dependency(
        'opengl',
    )
])

test('cop0 unit tests',
    executable(
        'cop0_test',
        'src/cpu/cop0/cop0_test.cpp',
        dependencies:
            dependency(
                'gtest',
                main: true,
                required: false
            )
    )
)