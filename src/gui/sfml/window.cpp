#include "window.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace {
    std::unique_ptr<sf::RenderWindow> window;
}

namespace gui { namespace sfml {
    void create_main_window() {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 480), "No game loaded...");
    /*
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::White);

        // Check if the window is open.
        while (window->isOpen()) {
            // Poll events from the computer.
            sf::Event event;
            while (window->pollEvent(event)) {
                // Do the user want to close the application?
                if (event.type == sf::Event::Closed) {
                    // Close window.
                    window->close();
                }
            }

            // Clear window.
            window->clear();
            // Draw.
            window->draw(shape);
            // Display what is drawn.
            window->display();
        }
    */
    }
}}