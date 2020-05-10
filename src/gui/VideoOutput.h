#pragma once
#include <wx/glcanvas.h>

// Main video output window.
class VideoOutput : public wxGLCanvas {
public:
    VideoOutput(wxWindow* parent);

    // Handle paint event.
    void OnPaint(wxPaintEvent& WXUNUSED(event));

private:
    wxGLContext *m_opengl_context;

protected:
    DECLARE_EVENT_TABLE()
};

