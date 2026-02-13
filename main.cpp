#include <SFML/Graphics.hpp>
#include "Boid.h"

int main() {
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    sf::RenderWindow window(sf::VideoMode({winWidth, winHeight}), "SFML Flocking");
    //Boid boid;
    std::vector<Boid> boids(45);

    while (window.isOpen()) {
         while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        for (auto& boid : boids)
        {
            boid.checkForSeparation(boids);
        }

        for (auto& boid : boids)
        {
            boid.checkForAlignment(boids);
        }

        for (auto& boid : boids)
        {
            boid.checkForCohesion(boids);
        }
        
        for (auto& boid : boids)
        {
            boid.move(winWidth, winHeight);
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