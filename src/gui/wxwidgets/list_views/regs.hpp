#include <sstream>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../cmd.hpp"

class Regview : public wxListView {
public:
    Regview(wxFrame *f);

    // Set register.
    void set(const unsigned int i, const int64_t val);

    // Update the register view with the current value of the CPU registers.
    void update();

private:
    wxDECLARE_EVENT_TABLE();
    std::stringstream ss;
};
