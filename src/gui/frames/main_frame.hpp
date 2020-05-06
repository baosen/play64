#include <wx/wx.h>
#include <wx/aui/aui.h>
#include "../disasm.hpp"
#include "../list_views/regs.hpp"
#include "../cmd.hpp"

class MainFrame : public wxFrame {
public:
    MainFrame();
    ~MainFrame();
private:
    bool is_rom_loaded();
    CMD(File);
    CMD(Exit);
    CMD(About);
    CMD(Execute);
    CMD(Step);
    CMD(ExecuteTillBreakpoint);
    wxDECLARE_EVENT_TABLE();

    Disassembler *disassembler;
    Regview      *registers;

    wxAuiManager mgr; // multi-document manager.
};
