#include <wx/listctrl.h>
#include <wx/notebook.h>
#include "id.hpp"
#include "periph.hpp"
#include "list_views/viview.hpp"

Periph::Periph(wxFrame *f) : wxFrame(f, wxID_ANY, "Peripherals", wxDefaultPosition, wxDefaultSize) {
    auto nb  = new wxNotebook(this, ID_Notebook);
    auto tlb = new wxWindow(nb, wxID_ANY);
    auto vi  = new wxWindow(nb, wxID_ANY);
    auto ai  = new wxWindow(nb, wxID_ANY);
    auto pi  = new wxWindow(nb, wxID_ANY);
    auto si  = new wxWindow(nb, wxID_ANY);
    auto l1  = new Viview(vi);
    nb->AddPage(tlb, "TLB");
    nb->AddPage(vi, "VI");
    nb->AddPage(ai, "AI");
    nb->AddPage(pi, "PI");
    nb->AddPage(si, "SI");
}
