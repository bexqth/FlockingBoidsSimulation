#include "AvoidanceObstacle.h"
#include <iostream>

using namespace std;

AvoidanceObstacle::AvoidanceObstacle(sf::Vector2f position) : Obstacle(position)
{
    this->shape.setFillColor(sf::Color(255, 175, 100));
}

AvoidanceObstacle::~AvoidanceObstacle()
{
}
