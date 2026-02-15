#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

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

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                } else if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                }
            }
        }

        simulation.update(winWidth, winHeight);
        
        window.clear(sf::Color(40, 44, 52));
        simulation.draw(window);
        window.display();
    }
    return 0;
}   