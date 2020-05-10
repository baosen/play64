#include "framebuffer.h"

framebuffer::framebuffer() {}
framebuffer::~framebuffer() {}

// Set framebuffer virtual memory address.
void framebuffer::set_framebuffer_address(memory_address memory_address_to_set) {
    m_memory_address = memory_address_to_set;
}

// Get framebuffer virtual memory address.
memory_address framebuffer::get_framebuffer_address() const {
    return m_memory_address;
}

void framebuffer::set_main_window(wxWindow *ptr_to_main_window) {
    main_window = ptr_to_main_window;
}
