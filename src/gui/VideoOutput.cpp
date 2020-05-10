#include <wx/wx.h>
#include "VideoOutput.h"

BEGIN_EVENT_TABLE(VideoOutput, wxGLCanvas)
    EVT_PAINT(VideoOutput::OnPaint)
END_EVENT_TABLE()

VideoOutput::VideoOutput(wxWindow* parent)
    : wxGLCanvas( parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize, 0, "Video", wxNullPalette )
{
    m_opengl_context = new wxGLContext(this);
}

// Called on receiving paint event.
void VideoOutput::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    SetCurrent(*m_opengl_context);
    wxPaintDC dc(this);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glColor3f(0.4, 0.5, 0.4);
        glVertex2f(0.0, -0.8);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.1, 0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(0.1, -0.1);
    glEnd();

    glFlush();
    */

    SwapBuffers();
}
