#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "Simulation.h"

int main() {
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "SFML Flocking");
    //Boid boid;
    std::vector<Boid> boids(45);
    Simulation simulation;

    while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        simulation.update(winWidth, winHeight);
        
        window.clear(sf::Color(40, 44, 52));
        simulation.draw(window);
        window.display();
    }
    return 0;
}