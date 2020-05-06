#include "framebuffer.h"

framebuffer::framebuffer() {}
framebuffer::~framebuffer() {}

void framebuffer::set_framebuffer_address(memory_address memory_address_to_set) {
    m_memory_address = memory_address_to_set;

    // Create window for displaying video.
    assert(main_window != nullptr);
    video_window = new wxGLCanvas(
            main_window,
            wxID_ANY,
            nullptr,
            wxDefaultPosition,
            wxDefaultSize,
            0,
            "Video",
            wxNullPalette
    );

    // Create context for OpenGL.
    opengl_context = new wxGLContext(video_window);
}
memory_address framebuffer::get_framebuffer_address() const {
    return m_memory_address;
}

void framebuffer::set_main_window(wxWindow *ptr_to_main_window) {
    main_window = ptr_to_main_window;
}

void framebuffer::draw_to_screen() {
    // TODO!
}
