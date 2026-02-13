#include "Simulation.h"

Simulation::Simulation()
{
    this->boids.resize(40);
}

Simulation::~Simulation()
{
}

void Simulation::update(int winWidth, int winHeight)
{
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
}

void Simulation::draw(sf::RenderWindow &window)
{
    for (auto& boid : boids)
    {
        boid.draw(window);
    }
}
