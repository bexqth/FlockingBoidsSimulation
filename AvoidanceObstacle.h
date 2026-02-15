#pragma once
#include "Obstacle.h"

class AvoidanceObstacle : public Obstacle
{
private:

public:
    AvoidanceObstacle(sf::Vector2f position);
    ~AvoidanceObstacle();
};