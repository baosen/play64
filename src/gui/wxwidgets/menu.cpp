#include "menu.hpp"
#include "id.hpp"

// Create file menu.
wxMenu* filemenu() {
    wxMenu *f = new wxMenu;
#ifdef __linux__
    f->Append(ID_File, "&Open...\tCTRL+o", "Open a Nintendo 64 ROM file."); // Press CTRL+o to open the file dialog.
#else
    f->Append(ID_File, "&Open...\to", "Open a Nintendo 64 ROM file."); // Press o to open the file dialog.
#endif
    f->AppendSeparator();
    f->Append(wxID_ABOUT);
    f->Append(wxID_EXIT);
    return f;
}

// Create CPU menu.
wxMenu* cpumenu() {
    wxMenu *s = new wxMenu;
#ifdef __linux__
    s->Append(ID_Step,      "&Step\tCTRL+s", "Step a single instruction."); // Press CTRL+s to step.
    s->Append(ID_ExecuteTillBreakpoint, "&Execute to breakpoint\tCTRL+d", "Execute until breakpoint is hit."); // Press CTRL+d to execute to breakpoint.
    s->Append(ID_Execute,   "&Execute\tCTRL+e", "Execute program stored in the ROM."); // Press CTRL+e to execute game.
#else
    s->Append(ID_Step,      "&Step\ts", "Step a single instruction."); // Press s to step.
    s->Append(ID_ExecuteTillBreakpoint, "&Execute to breakpoint\td", "Execute until breakpoint is hit."); // Press d to execute to breakpoint.
    s->Append(ID_Execute,   "&Execute\te", "Execute program stored in the ROM."); // Press e to execute game.
#endif
    return s;
}

// Create top menu bar.
wxMenuBar* topmenu() {
    wxMenuBar *b = new wxMenuBar;
    b->Append(filemenu(), "&ROM");
    b->Append(cpumenu(), "&CPU");
    return b;
}
