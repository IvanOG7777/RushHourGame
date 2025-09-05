// If your project uses precompiled headers (most VS C++ templates do):
         // or "stdafx.h" for older projects

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> // redundant when including Graphics, but harmless
#include <SFML/System.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    window.setFramerateLimit(60);

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(200.f, 150.f);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }
    return 0;
}
