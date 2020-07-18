#include "cmd.hpp"
#include "../../memory_map/memaddr.hpp"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <sstream>

class Disassembler : public wxListView {
public:
    // Create the disassembler.
    Disassembler(wxFrame* f, const memory_address base);

    // Clear all instructions.
    void clear();

    // Add an instruction to the list.
    void add(const u32 addr, const char* text);

    // Select an instruction.
    void select(const memory_address addr);

    // Deselect an instruction.
    void deselect(const memory_address addr);

    // Fill with instructions.
    void fill();

    // Refill with instructions.
    void refill(const memory_address base);

private:
    CTX(Ctx);
    CMD(Break);
    DECLARE_EVENT_TABLE();
    int id, rows;
    std::stringstream ss;
    memory_address base;
};
