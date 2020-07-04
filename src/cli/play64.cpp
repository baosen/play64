#include "../gui/sfml/window.h"
#include "../memory_map/physical_memory/cart/pak.hpp"
#include <iostream>
#include <cstdlib>

static const char cli_executable_name[] = "play64";

// play64: Play Nintendo 64 ROMs from the command-line.
int main(const int argc, const char* argv[]) {
    // Is there any arguments provided?
    if (argc <= 1) {
        // No arguments provided.
        std::cerr << "Error: No file path to a Nintendo 64 ROM provided..."  << std::endl
                  << "Usage: " << cli_executable_name << " <file path to Nintendo 64 ROM>"
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Load a Nintendo 64 ROM file into memory from a given file path.
    const auto rom_file_path = argv[1];
    Pak::load(rom_file_path);

    // Create the main window.
    gui::sfml::create_main_window();
    return EXIT_SUCCESS;
}