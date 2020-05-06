#include <sstream>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../cmd.hpp"
#include "../../data_types/types.hpp"

class Regview : public wxListView {
public:
    Regview(wxFrame *f);

    // Set register.
    void set(const uint i, const s64 val);
    // Update the register view with the current value of the CPU registers.
    void update();
private:
    wxDECLARE_EVENT_TABLE();
    std::stringstream ss;
};
