#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position) : position(position)
{
    this->radius = 10.0f;
    this->conflicArea = 20.0f;
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
}

sf::Vector2f Obstacle::getPosition() const
{
    return this->position;
}
