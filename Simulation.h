#pragma once
#include <vector>
#include "Boid.h"
#include "AttractionObstacle.h"
#include "AvoidanceObstacle.h"

class Simulation
{
private:
    std::vector<Boid> boids;
    std::vector<Obstacle*> allObstacles;
    
public:
    Simulation();
    ~Simulation();
    void update(int winWidth, int winHeight);
    void draw(sf::RenderWindow &window);
    void handleMouseClick(sf::RenderWindow &window, sf::Mouse::Button button, sf::Vector2i mousePos);
    void createObstacle(sf::Mouse::Button button);
    void eraseObstacle(Obstacle* foundObstacle);
    Obstacle* checkIfClickedObstacle(sf::Vector2i mousePos);
};
