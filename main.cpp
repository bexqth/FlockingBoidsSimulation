#include <SFML/Graphics.hpp>
#include "Boid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Test");
    Boid boid;

    while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        boid.move();
        window.clear(sf::Color(40, 44, 52));
        boid.draw(window);
        window.display();
    }
    return 0;
}