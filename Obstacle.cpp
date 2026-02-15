#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position) : position(position)
{
    this->radius = 10.0f;
    this->conflicArea = 20.0f;
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
    return false;
}

sf::Vector2f Obstacle::getPosition() const
{
    return this->position;
}
