#include <SFML/Graphics.hpp>
#include "Boid.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Test");
    //Boid boid;
    std::vector<Boid> boids(30);

    while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        for (auto& boid : boids)
        {
            boid.move();
        }
        
        //boid.move();
        window.clear(sf::Color(40, 44, 52));
        //boid.draw(window);
        for (auto& boid : boids)
        {
            boid.draw(window);
        }
        window.display();
    }
    return 0;
}