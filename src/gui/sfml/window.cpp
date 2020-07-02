#include "window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

namespace {
    std::unique_ptr<sf::RenderWindow> window;

    // Clear window.
    void clear_window() {
        assert(window->isOpen());
        window->clear();
    }

    // Display what is drawn in the framebuffer.
    void display() {
        assert(window->isOpen());
        window->display();
    }
}

namespace gui { namespace sfml {
    void create_main_window() {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 480), "No game loaded...");
    }

    void output_16bit_image(char framebuffer[]) {
        assert(window != nullptr);
        clear_window();
    }

    void output_32bit_image(char framebuffer[]) {
        assert(window != nullptr);
        clear_window();
    }
}}