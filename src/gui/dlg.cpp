#include <wx/filedlg.h>
#include "dlg.hpp"

// Ask the user to load a ROM using the file dialog.
// Returns the path to the ROM file.
wxString ask_user_for_rom(wxFrame *frm)
{
    // Ask user to load the N64 ROM file.
    wxFileDialog o(frm, 
                   _("Open a Nintendo 64 ROM."), 
                   "", "", 
                   "All files (*.*)|*.*",             // Show all files.
                   wxFD_OPEN | wxFD_FILE_MUST_EXIST); // The file should be opened and must exist.

    // If user pressed the cancel button.
    switch (o.ShowModal()) {
    case wxID_OK:
        return o.GetPath();
    case wxID_CANCEL: default:
        break;
    }
    return "";
}
