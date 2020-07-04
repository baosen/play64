#include "window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

namespace {
    std::unique_ptr<sf::RenderWindow> window;
    sf::Texture video_output;
    sf::Sprite screen;

    // Clear the main window.
    void clear_main_window() {
        assert(window->isOpen());
        window->clear();
    }
}

namespace gui { namespace sfml {
    // Create the main window to display the video output screen.
    void create_main_window() {
        // Create a new window.
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(100, 100), "No game loaded...");
        screen = sf::Sprite(video_output);
    }

    // Set the video screen's resolution.
    void set_video_resolution(const unsigned int horizontal_resolution, const unsigned int vertical_resolution) {
        window->setSize(sf::Vector2u(horizontal_resolution, vertical_resolution));
    }

    // Output 16-bit color image pixels from framebuffer to screen inside the window.
    void output_16bit_image(char framebuffer[]) {
        assert(window != nullptr);
        assert(window->isOpen());

        clear_main_window();
        // TODO: Convert 16-bit color pixels to 32-bit RBGA color pixels.
    }

    // Output 32-bit color image from framebuffer to screen inside the window.
    void output_32bit_image(char framebuffer[]) {
        assert(window != nullptr);

        clear_main_window();
        window->draw(screen);
        window->display();
    }
}}