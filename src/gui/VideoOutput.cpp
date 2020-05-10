#include "VideoOutput.h"

VideoOutput::VideoOutput(wxWindow* parent)
    : wxGLCanvas( parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize, 0, "Video", wxNullPalette )
{
    // Create context for OpenGL.
    opengl_context = new wxGLContext(this);
}
