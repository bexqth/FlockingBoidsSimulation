#include "Boid.h"
#include <iostream>
#include <random>

using namespace std;

Boid::Boid()
{
    this->speed = 0.05f;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrX(100, 700);
    uniform_int_distribution<> distrY(100, 500);

    std::uniform_real_distribution<> distrRadiusX(0, 0.1);
    std::uniform_real_distribution<> distrRadiusY(0, 0.1);

    float randomXPos = distrX(gen);
    float randomYPos = distrY(gen);
    this->radius = 7.f;
    this->shape = sf::CircleShape(this->radius, 3);
    this->shape.setScale({1.0f, 2.0f});
    this->shape.setFillColor(sf::Color(85, 141, 246));

    this->position = sf::Vector2f(randomXPos, randomYPos);
    float vectorX = distrRadiusX(gen);
    float vectorY = distrRadiusY(gen);
    this->rotate(vectorY, vectorX);
    cout << "vectorX: " << vectorX << " vectorY: " << vectorY << endl;
    float vectorLength = sqrt(pow(vectorX,2) + pow(vectorY,2));

    vectorX = vectorX / vectorLength;
    vectorY = vectorY / vectorLength;
    cout << "Normalized vector" << endl;
    cout << "vectorX: " << vectorX << " vectorY: " << vectorY << endl;

    cout << " " << endl;
    this->velocity = sf::Vector2f(vectorX * this->speed, vectorY * this->speed);
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
    this->rotate(this->velocity.y, this->velocity.x);
    this->shape.setPosition(this->position);
    //this->acceleration = sf::Vector2f(.0f, .0f);

    if (this->position.x > 800 + this->radius) {
        this->position.x = -this->radius;
    } else if (this->position.x < -this->radius) {
        this->position.x = 800 + this->radius;
    }

    if (this->position.y > 600 + this->radius) {
        this->position.y = -this->radius;
    } else if (this->position.y < -this->radius) {
        this->position.y = 600 + this->radius;
    }
    
}

void Boid::checkForSeparation(vector<Boid>& boidVector) 
{   
    sf::Vector2f averageBoidsVector = sf::Vector2f(0,0);
    float radiusDistance = 40.f;
    int count = 0;

    for (auto& boid : boidVector)
    {
        if(&boid != this) {
            float distanceX = boid.getPosition().x - this->position.x;
            float distanceY = boid.getPosition().y - this->position.y;
            float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
            if (distance <= radiusDistance) {
                //averageBoidsVector += sf::Vector2f(distanceX, distanceY);
                averageBoidsVector += sf::Vector2f(distanceX / distance, distanceY / distance);
                count++;
            }
        }
    }

    if(count > 0) {
        sf::Vector2f oppositeVector = -averageBoidsVector;
        float vectorLength = sqrt(oppositeVector.x * oppositeVector.x + oppositeVector.y * oppositeVector.y);

        float vectorX = oppositeVector.x / vectorLength;
        float vectorY = oppositeVector.y / vectorLength;

        oppositeVector = sf::Vector2f(vectorX * this->speed, vectorY * this->speed);
        this->velocity = (this->velocity * 0.95f) + (oppositeVector * 0.05f);

        vectorLength = sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
        this->velocity = sf::Vector2f((this->velocity.x / vectorLength) * this->speed, (this->velocity.y / vectorLength) * this->speed);

        this->rotate(this->velocity.y, this->velocity.x);
    }

}



sf::Vector2f Boid::getPosition()
{
    return this->position;
}

void Boid::rotate(float vectorY, float vectorX)
{
    float rotation = atan2(vectorY, vectorX);
    this->shape.setRotation(sf::radians(rotation) + sf::radians(1.57079633));
}
