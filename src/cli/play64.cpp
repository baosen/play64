#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "No game loaded...");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::White);

    // Check if the window is open.
    while (window.isOpen()) {
        // Poll events from the computer.
        sf::Event event;
        while (window.pollEvent(event)) {
            // Do the user want to close the application?
            if (event.type == sf::Event::Closed) {
                // Close window.
                window.close();
            }
        }

        // Clear window.
        window.clear();
        // Draw.
        window.draw(shape);
        // Display what is drawn.
        window.display();
    }
    return EXIT_SUCCESS;
}