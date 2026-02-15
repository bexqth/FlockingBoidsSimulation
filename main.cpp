#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

int main() {
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "Flocking simulation");
    window.requestFocus();
    
    std::vector<Boid> boids(45);
    Simulation simulation;

    while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>())
            {
                std::cout << "Event button: " << (int)mouseButtonPressed->button << std::endl;
                auto mousePosVector = sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                simulation.handleMouseClick(window, mouseButtonPressed->button, mousePosVector);
            }
        }

        simulation.update(winWidth, winHeight);
        
        window.clear(sf::Color(40, 44, 52));
        simulation.draw(window);
        window.display();
    }
    return 0;
}   