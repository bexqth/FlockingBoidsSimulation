#include "Boid.h"

Boid::Boid()
{
    this->shape = sf::CircleShape(15.f, 3);
    this->shape.setScale({1.0f, 2.0f});
    this->shape.setFillColor(sf::Color(85, 141, 246));

    this->position = sf::Vector2f(300.f, 275.f);
    this->velocity = sf::Vector2f(0.01f, 0.01f);
    //this->acceleration = sf::Vector2f(0.001f, 0.f);
    
    this->shape.setPosition(this->position);

}

Boid::~Boid()
{

}

void Boid::update()
{

}

void Boid::draw(sf::RenderWindow &window)
{
    window.draw(this->shape);
}

void Boid::move()
{
    this->position += this->velocity;
    //this->velocity += this->acceleration;
    this->shape.setPosition(this->position);
    //this->acceleration = sf::Vector2f(.0f, .0f);
}
