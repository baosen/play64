#include "frames/main_frame.hpp"

class App: public wxApp {
public:
    virtual bool OnInit();
};

bool App::OnInit()
{
    auto main_frame = new MainFrame();
    main_frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(App);
