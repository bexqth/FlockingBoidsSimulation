#include "Obstacle.h"
#include <iostream>

using namespace std;

Obstacle::Obstacle(sf::Vector2f position) : position(position)
{
    this->radius = 10.0f;
    this->position = position;
    this->shape.setRadius(this->radius);
    this->shape.setOrigin(sf::Vector2f(this->radius, this->radius));
    this->shape.setPosition(this->position);
}

Obstacle::~Obstacle()
{

}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(this->shape);
}

bool Obstacle::isMouseClicked(sf::Vector2i mousePosition)
{
    float xDiff = mousePosition.x - this->position.x;
    float yDiff = mousePosition.y - this->position.y;
    float distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));
    if(distance <= this->radius) {
        return true;
    }
    return false;
}

sf::Vector2f Obstacle::getPosition() const
{
    return this->position;
}
