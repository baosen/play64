#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "No game loaded...");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return EXIT_SUCCESS;
}