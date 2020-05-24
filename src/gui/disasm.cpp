#include <iomanip>
#include "disasm.hpp"
#include "dbg.hpp"
#include "id.hpp"
#include "../cpu/interpreter/instrsz.hpp"
#include "../memory_map/virtual_memory/vmem.hpp"
#include "../disassembler/decode.hpp"
using namespace std;

// Event callbacks.
BEGIN_EVENT_TABLE(Disassembler, wxListView)
    EVT_CONTEXT_MENU(Disassembler::Ctx)
    EVT_MENU(ID_Break, Disassembler::Break)
END_EVENT_TABLE()

// Construct the MIPS disassembler.
Disassembler::Disassembler(wxFrame* f, const memory_address b)
    : wxListView(f), id(0), rows(0), base(b) {
    InsertColumn(0, "Address");
    InsertColumn(1, "Instructions");
    ss << hex << setw(8);
}

// Clear and remove all instructions from the list.
void Disassembler::clear() {
    if (GetItemCount() > 0) {
        DeleteAllItems();
        rows = 0;
    }
}

// Add instruction to the list.
void Disassembler::add(const u32 addr, const char* instr) {
    ss.str("");
    ss << addr;
    InsertItem(rows, ss.str().c_str());
    SetItem(rows++, 1, instr);
}

// Refill the disassembler view with new instructions from a new base address.
void Disassembler::refill(const memory_address b) {
    clear();
    base = b;
    fill();
}

// Select an instruction marking it yellow.
void Disassembler::select(const memory_address addr) {
    // Find index of statement.
    int i = (addr-base)/4;
    // If outside boundary, then refill.
    if (i < 0 || i >= GetItemCount()) {
        refill(addr);
        // Recompute index from new base address.
        i = (addr-base)/4;
    }
    // Mark it yellow.
    SetItemBackgroundColour(i, wxColour(255, 255, 0));
}

// Select an instruction marking it back to its original colour.
void Disassembler::deselect(const memory_address addr) {
    // Is address is a breakpoint?
    if (Dbg::isbp(addr)) {
        // Set it back to red.
        SetItemBackgroundColour((addr - base) / 4, wxColour(255, 0, 0));
        return;
    }

    // Mark executed once.
    SetItemBackgroundColour((addr - base) / 4, 
                            wxColour(255, 255, 255)); // White colour.
                            //wxColour(100, 100, 100));
}

// Callback called when the user right clicks to show the right-click popup menu.
DCTXU(Disassembler, Ctx) {
    if (GetFocusedItem() < 0)
        return;

    wxMenu p;
#ifdef __linux__
    p.Append(ID_Break, _("&Break\tb"));      // Press b to set breakpoint.
    p.Append(ID_Assemble, _("&Assemble\tEnter")); // Press Enter to assemble.
#else
    p.Append(ID_Break, _("&Break\tb"));           // Press b to set breakpoint.
    p.Append(ID_Assemble, _("&Assemble\tEnter")); // Press Enter to assemble.
#endif
    PopupMenu(&p);
}

// Click on breakpoint-button.
DCMDU(Disassembler, Break) {
    const auto i = GetFocusedItem();
    // Did not the user mark an item?
    if (i == -1)
        return;
    SetItemBackgroundColour(i, wxColour(255, 0, 0));
    Select(i, false);
    Dbg::bpset(base+(i*INSTR_SIZE));
}

// Fill the disassembly with instructions in the memory.
void Disassembler::fill() {
    // Fill disassembly view with instructions.
    for (auto i = base; i < base+(INSTR_SIZE*1000); i += 4)
        add(i, decode(Vmem::rd32(i)).c_str());
}
