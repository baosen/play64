#pragma once
#include "../memaddr.hpp"
#include <wx/glcanvas.h>

// The Nintendo 64 system's frame buffer.
class framebuffer {
public:
    // Returns the only single instance of the framebuffer.
    static framebuffer& get_instance() {
        static framebuffer instance;
        return instance;
    }

    // Set the virtual memory address of the origin of the framebuffer.
    void set_framebuffer_address(memory_address memory_address_to_set);
    // Get the virtual memory address of the origin of the framebuffer.
    memory_address get_framebuffer_address() const;

    void set_main_window(wxWindow *ptr_to_main_window);

    // Draw framebuffer to screen.
    void draw_to_screen();
private:
    framebuffer();
    ~framebuffer();

    memory_address m_memory_address;

    wxGLCanvas *video_window;
    wxGLContext  *opengl_context;

    wxWindow *main_window;
};
