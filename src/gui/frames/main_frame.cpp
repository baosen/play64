#include <wx/wfstream.h>
#include "../../cpu/interpreter/err.hpp"
#include "../../cpu/interpreter/pc.hpp"
#include "../../memory_map/pak.hpp"
#include "../menu.hpp"
#include "../id.hpp"
#include "../dlg.hpp"
#include "../dbg.hpp"
#include "../../cpu/interpreter/interp.hpp"
#include "main_frame.hpp"

// Event callbacks.
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_File, MainFrame::File)
    EVT_MENU(ID_Execute, MainFrame::Execute)
    EVT_MENU(ID_Step, MainFrame::Step)
    EVT_MENU(ID_ExecuteTillBreakpoint, MainFrame::ExecuteTillBreakpoint)
    EVT_MENU(wxID_EXIT, MainFrame::Exit)
    EVT_MENU(wxID_ABOUT, MainFrame::About)
wxEND_EVENT_TABLE()

#define APPLICATION_NAME "Play64! A Nintendo 64 emulator."

// Create main frame.
MainFrame::MainFrame() : wxFrame(nullptr,
                                 wxID_ANY,
                                 APPLICATION_NAME,                  // Name of the application.
                                 wxDefaultPosition, wxDefaultSize), // Position and size of frame.
                     disassembler(new Disassembler(this, ENTRY_POINT)),
                     registers(new Regview(this)),
                     main_video_window(new VideoOutput(this))
{
    // Create top menu bar.
    SetMenuBar(topmenu());
    CreateStatusBar();

    // Set this frame to be managed by the docking window.
    mgr.SetManagedWindow(this);

    // Setup docking.
    mgr.AddPane(disassembler, wxCENTER, _("Disassembly"));
    mgr.AddPane(registers, wxRIGHT, _("Registers"));
    mgr.AddPane(main_video_window, wxRIGHT, _("Video"));
    mgr.Update();

    // Start maximized.
    Maximize(true);
}

MainFrame::~MainFrame() {
    mgr.UnInit();
}

// Exit the program.
DCMDU(MainFrame, Exit) {
    Close(true);
}

// Show who wrote this program.
DCMDU(MainFrame, About) {
    wxMessageBox(APPLICATION_NAME"\n"
                 "\n"
                 "A Nintendo 64 emulator.\n"
                 "Built on " __DATE__ ".\n"
                 "\n"
                 "Copyright (c) Bao Chi Tran Nguyen", "About", wxOK | wxICON_INFORMATION);
}

// Open the file dialog.
DCMDU(MainFrame, File) {
    // Load ROM into pak.
    const auto path = ask_user_for_rom(this);

    // If user has not specified any ROM.
    if (path.IsSameAs("")) {
        SetStatusText("No ROM-file specified...");
        return;
    }

    try {
        // Clear all instructions.
        disassembler->clear();

        // Load ROM file into Game Pak ROM memory.
        Pak::load(path.c_str());

        // Tell the user that the ROM was successfully is_rom_loaded!
        SetStatusText("Successfully loaded ROM: " + path);
    } catch (const err& e) {
        // Tell the user about the error (exception) that happened.
        SetStatusText(e.what());
        return;
    }

    // Fill disassembly with instructions.
    disassembler->fill();

    // Mark instruction pointed by the program counter (instruction pointer).
    disassembler->select(ENTRY_POINT);
}

// Is ROM been loaded into the virtual memory?
bool MainFrame::is_rom_loaded() {
    // Check if the ROM has been loaded into the virtual memory.
    if (Pak::is_rom_loaded()) {
        return true;
    }

    // Tell user that no ROM has been loaded.
    SetStatusText("No Nintendo 64 ROM file has been loaded!");
    return false;
}

// Execute the game that has been loaded in memory.
DCMDU(MainFrame, Execute) {
    if (!is_rom_loaded())
        return;

    try {
        // De-select current instruction.
        disassembler->deselect(Cpu::pc);

        // Run the game.
        for (;;)
            Interpreter::step();

    } catch (const err& e) {
        // Set view to show the instruction it errored on.
        registers->update();
        disassembler->select(Cpu::pc);

        // Tell the user about the error.
        SetStatusText(e.what());
    } catch (...) {
        registers->update();
        disassembler->select(Cpu::pc);
        SetStatusText("Exception caught! Something went wrong :(.");
    }
}

// Step a single instruction in the disassembler view.
DCMDU(MainFrame, Step) {
    try {
        if (!is_rom_loaded())
            return;

        disassembler->deselect(Cpu::pc);

        Interpreter::step();
        registers->update();
        disassembler->select(Cpu::pc);
    } catch (const err& e) {
        registers->update();
        disassembler->select(Cpu::pc);
        SetStatusText(e.what());
    } catch (...) {
        registers->update();
        disassembler->select(Cpu::pc);
        SetStatusText("Exception caught! Something went wrong :(.");
    }
}

// Execute until breakpoint is hit.
DCMDU(MainFrame, ExecuteTillBreakpoint) {
    // Check if the user has loaded a ROM.
    if (!is_rom_loaded())
        return;

    // Check if the user has set any breakpoints.
    if (Dbg::has_user_set_any_breakpoints()) {
        SetStatusText("No breakpoint has been set!");
        return;
    }

    try {
        // De-select current instruction.
        disassembler->deselect(Cpu::pc);

        // Execute an instruction and break on the next instruction.
        while (!Dbg::breakstep()) {}

        // Update the registry view with current state of the CPU registers.
        registers->update();
        disassembler->select(Cpu::pc);
    } catch (const err& e) {
        registers->update();
        disassembler->select(Cpu::pc);
        SetStatusText(e.what());
    } catch (...) {
        registers->update();
        disassembler->select(Cpu::pc);
        SetStatusText("Exception caught! Something went wrong :(.");
    }
}
