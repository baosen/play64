#pragma once
#include <wx/glcanvas.h>

// Main video output window.
class VideoOutput : public wxGLCanvas {
public:
    VideoOutput(wxWindow* parent);
private:
    wxGLContext  *opengl_context;
};

