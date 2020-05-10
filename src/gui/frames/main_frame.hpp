#include <wx/wx.h>
#include <wx/aui/aui.h>
#include "../disasm.hpp"
#include "../list_views/regs.hpp"
#include "../cmd.hpp"
#include "../VideoOutput.h"

class MainFrame : public wxFrame {
public:
    MainFrame();
    ~MainFrame();
private:
    bool is_rom_loaded();

    // File menu commands.
    CMD(File);
    CMD(Exit);
    CMD(About);
    CMD(Execute);
    CMD(Step);
    CMD(ExecuteTillBreakpoint);

    wxDECLARE_EVENT_TABLE();

    Disassembler *disassembler;
    Regview      *registers;
    VideoOutput *main_video_window;

    wxAuiManager mgr; // multi-document manager.
};
