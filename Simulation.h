#pragma once
#include <vector>
#include "Boid.h"

class Simulation
{
private:
    std::vector<Boid> boids;

public:
    Simulation();
    ~Simulation();
    void update(int winWidth, int winHeight);
    void draw(sf::RenderWindow &window);
};
