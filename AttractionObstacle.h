#pragma once
#include "Obstacle.h"

class AttractionObstacle : public Obstacle
{
private:
   
public:
    AttractionObstacle(sf::Vector2f position);
    ~AttractionObstacle();
    void update() override;
};

