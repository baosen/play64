#include <wx/wx.h>
#include <wx/listctrl.h>
#include "viview.hpp"

Viview::Viview(wxWindow* w) : wxListView(w, wxID_ANY) {
    this->InsertColumn(0, "Registers");
    this->InsertColumn(1, "Hex");
    this->InsertColumn(2, "Value");
}
