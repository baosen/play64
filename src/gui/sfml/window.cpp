#include "window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

namespace {
    std::unique_ptr<sf::RenderWindow> window;

    // Clear the main window.
    void clear_main_window() {
        assert(window->isOpen());
        window->clear();
    }

    // Display what is drawn in the framebuffer.
    void display_framebuffer() {
        assert(window->isOpen());
        window->display();
    }
}

namespace gui { namespace sfml {
    void create_main_window() {
        // Create a new window.
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(100, 100), "No game loaded...");
    }

    void set_video_resolution(const unsigned int horizontal_res, const unsigned int vertical_res) {
        window->setSize(sf::Vector2u(horizontal_res, vertical_res));
    }

    void output_16bit_image(char framebuffer[]) {
        assert(window != nullptr);
        clear_main_window();
    }

    void output_32bit_image(char framebuffer[]) {
        assert(window != nullptr);
        clear_main_window();
    }
}}