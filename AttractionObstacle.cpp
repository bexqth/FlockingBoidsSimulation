#include "AttractionObstacle.h"
#include <iostream>

using namespace std;

AttractionObstacle::AttractionObstacle(sf::Vector2f position) : Obstacle(position)
{
    this->shape.setFillColor(sf::Color(200, 114, 147));
    //cout << position.x << " " << position.y << endl;
}

AttractionObstacle::~AttractionObstacle()
{

}

