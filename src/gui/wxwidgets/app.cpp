#include "frames/main_frame.hpp"

class App: public wxApp {
public:
    virtual bool OnInit();
};

bool App::OnInit()
{
    return (new MainFrame())->Show(true);
}

wxIMPLEMENT_APP(App);
