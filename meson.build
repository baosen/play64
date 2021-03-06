project(
    'play64!',
    'cpp',
    license: 'GPL3',
    default_options: [
        'cpp_std=c++2a',
    ]
)

unused_cli_code = [
    #'src/cli/args.cpp',
    #'src/cli/cmdparams.cpp',
    #'src/cli/cstr.cpp',
    #'src/cli/debug.cpp',
    #'src/cli/printstep.cpp',
    #'src/cli/trace.cpp',
]

main_include_directory = include_directories('src/')

sources = [
    'src/memory_map/mem.cpp',
    'src/memory_map/byteswap.cpp',
    'src/memory_map/physical_memory/ai/ai.cpp',
    'src/memory_map/physical_memory/si/pif/cic/cic6105.cpp',
    'src/memory_map/physical_memory/physmem.cpp',
    'src/memory_map/physical_memory/pi/pi.cpp',
    'src/memory_map/physical_memory/si/pif/pif.cpp',
    'src/memory_map/physical_memory/rdram/rdram.cpp',
    'src/memory_map/physical_memory/mi/mi.cpp',
    'src/memory_map/physical_memory/cart/pak.cpp',
    'src/memory_map/physical_memory/ri/ri.cpp',
    'src/memory_map/physical_memory/si/si.cpp',
    'src/memory_map/physical_memory/sp/sp.cpp',
    'src/memory_map/physical_memory/dp/dp.cpp',
    'src/memory_map/physical_memory/vi/vi.cpp',
    'src/memory_map/physical_memory/vi/control/control.cpp',
    'src/memory_map/virtual_memory/vmem.cpp',
    'src/cpu/interpreter/normals/cop0/tlb/tlb.cpp',
    'src/cpu/interpreter/normals/cop0/tlb/tlbops.cpp',
    'src/cpu/interpreter/normals/cop0/tlb/tlbstr.cpp',
    'src/cpu/interpreter/normals/cop0/cop0.cpp',
    'src/cpu/interpreter/normals/cop0/cop0str.cpp',
    'src/cpu/interpreter/normals/cop0/syscon.cpp',
    'src/cpu/interpreter/normals/cop1/fpu/fpu.cpp',
    'src/cpu/interpreter/normals/cop1/cop1.cpp',
    'src/cpu/interpreter/normals/cop1/cop1str.cpp',
    'src/cpu/interpreter/normals/regimms/regimms.cpp',
    'src/cpu/interpreter/normals/regimms/regimmsstr.cpp',
    'src/cpu/interpreter/normals/specials/specials.cpp',
    'src/cpu/interpreter/normals/specials/specialsstr.cpp',
    'src/cpu/interpreter/normals/normals.cpp',
    'src/cpu/interpreter/normals/normalsstr.cpp',
    'src/cpu/interpreter/registers/cpu.cpp',
    'src/cpu/interpreter/instr.cpp',
    'src/cpu/interpreter/interp.cpp',
    'src/cpu/interpreter/sext.cpp',
    'src/disassembler/decode.cpp',
    'src/disassembler/hex.cpp',
    'src/disassembler/hex_address_stream.cpp',
    'src/disassembler/strings.cpp',
    'src/disassembler/strmanip.cpp',
    'src/cartridge/manufacts.cpp',
    'src/signal.cpp',
    'src/logging/log.cpp',
]

executable(
    'play64-gui',
    sources + [
        'src/gui/wxwidgets/app.cpp',
        'src/gui/wxwidgets/dbg.cpp',
        'src/gui/wxwidgets/disasm.cpp',
        'src/gui/wxwidgets/dlg.cpp',
        'src/gui/wxwidgets/frames/main_frame.cpp',
        'src/gui/wxwidgets/menu.cpp',
        'src/gui/wxwidgets/periph.cpp',
        'src/gui/wxwidgets/list_views/regs.cpp',
        'src/gui/wxwidgets/list_views/viview.cpp',
        'src/gui/wxwidgets/VideoOutput.cpp',
    ],
    include_directories: main_include_directory,
    dependencies: [
        dependency(
            'wxwidgets',
            version: '>=3.0.0',
            modules: ['core','base', 'aui', 'gl']
        ),
        dependency(
            'opengl',
        )
    ]
)

sfml = dependency('sfml-all')

executable(
    'play64-cli',
    sources + [
        'src/gui/sfml/window.cpp',
        'src/cli/play64.cpp'
    ],
    include_directories: main_include_directory,
    dependencies: [sfml],
    cpp_args: '-DSFML'
)

gtest = dependency(
    'gtest',
    main: true,
    required: false
)

test('cop0',
    executable(
        'cop0_test',
        'src/cpu/interpreter/normals/cop0/cop0_test.cpp',
        dependencies: gtest
    )
)

test('sfml::window',
    executable(
        'window_test',
        'src/gui/sfml/window.cpp',
        dependencies: [gtest, sfml]
    )
)

test('vi',
    executable(
        'vi_test',
        'src/memory_map/physical_memory/vi/vi_test.cpp',
        dependencies: gtest
    )
)

test('vi::control',
    executable(
        'control_test',
        'src/memory_map/physical_memory/vi/control/control.cpp',
        'src/memory_map/physical_memory/vi/control/control_test.cpp',
        dependencies: gtest
    )
)