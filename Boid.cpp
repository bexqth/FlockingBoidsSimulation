#include "Boid.h"
#include <iostream>
#include <random>
#include "AttractionObstacle.h"

using namespace std;

Boid::Boid()
{
    //this->speed = 0.04f;
    this->speed = 0.05f;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrX(100, 900);
    uniform_int_distribution<> distrY(100, 500);

    std::uniform_real_distribution<> distrRadiusX(0, 0.1);
    std::uniform_real_distribution<> distrRadiusY(0, 0.1);

    float randomXPos = distrX(gen);
    float randomYPos = distrY(gen);
    this->radius = 5.f;
    this->shape = sf::CircleShape(this->radius, 3);
    this->shape.setScale({1.0f, 1.0f});
    this->shape.setFillColor(sf::Color(85, 141, 246));
    this->shape.setOrigin(sf::Vector2f(this->radius, this->radius));

    this->position = sf::Vector2f(randomXPos, randomYPos);
    float vectorX = distrRadiusX(gen);
    float vectorY = distrRadiusY(gen);
    this->rotate(vectorY, vectorX);
    std::pair<sf::Vector2f, bool> normalizedVec = this->normalizeVector(sf::Vector2f(vectorX, vectorY));
    if (normalizedVec.second) {
        this->velocity = normalizedVec.first * this->speed;
    }

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

void Boid::move(int maxWidth, int maxHeight)
{
    this->position += this->velocity;
    this->checkWindowBorders(maxWidth, maxHeight);
    this->rotate(this->velocity.y, this->velocity.x);
    this->shape.setPosition(this->position);
}

void Boid::checkWindowBorders(int maxWidth, int maxHeight)
{
    float step = 10.0f;
    if (this->position.x + this->radius + step > maxWidth) {
        this->velocity.x *= -1;
        this->position.x = maxWidth - this->radius - step;

    } else if (this->position.x - this->radius - step < 0) {
        this->velocity.x *= -1;
        this->position.x = this->radius + step;
    }

    if (this->position.y + this->radius + step > maxHeight) {
        this->velocity.y *= -1;
       this->position.y = maxHeight - this->radius - step;

    } else if (this->position.y - this->radius - step < 0) {
         this->velocity.y *= -1;
        this->position.y = this->radius + step;
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
                averageBoidsVector += sf::Vector2f(distanceX / distance, distanceY / distance);
                count++;
            }
        }
    }

    if(count > 0) {
        sf::Vector2f oppositeVector = -averageBoidsVector;
        std::pair<sf::Vector2f, bool> normalizedOpposite = this->normalizeVector(oppositeVector);
        if (normalizedOpposite.second) {
            this->velocity = (this->velocity * 0.95f) + ((normalizedOpposite.first * this->speed) * 0.05f);
            std::pair<sf::Vector2f, bool> normalizedVelocity = this->normalizeVector(this->velocity);
            if (normalizedVelocity.second) {
                this->velocity = normalizedVelocity.first * this->speed;
            }
        }
    }

}

void Boid::checkForAlignment(std::vector<Boid> &vector)
{
    float radiusDistance = 60.f;
    sf::Vector2f averageVelocity = sf::Vector2f(0,0);
    int count = 0;

    for(auto& boid: vector) {
        if(&boid != this) {
            float distanceX = boid.getPosition().x - this->position.x;
            float distanceY = boid.getPosition().y - this->position.y;
            float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
            if (distance <= radiusDistance) {
                averageVelocity += sf::Vector2f(boid.getVelocity().x, boid.getVelocity().y);
                count++;
            }
        }       
    }

    if (count > 0) {
        averageVelocity = sf::Vector2f(averageVelocity.x / count, averageVelocity.y / count);
        this->velocity = (this->velocity * 0.95f) + (averageVelocity * 0.05f);
        std::pair<sf::Vector2f, bool> normalizedVelocity = this->normalizeVector(this->velocity);
        if (normalizedVelocity.second) {
            this->velocity = normalizedVelocity.first * this->speed;
        }
    }
    
}

void Boid::checkForCohesion(std::vector<Boid> &vector)
{
    float radiusDistance = 60.f;
    float averageX = 0;
    float averageY = 0;
    int count = 0;

    for(auto& boid : vector) {
        if(&boid != this) {
            float distanceX = boid.getPosition().x - this->position.x;
            float distanceY = boid.getPosition().y - this->position.y;
            float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
            if (distance <= radiusDistance) {
                averageX += boid.getPosition().x;
                averageY += boid.getPosition().y;
                count++;
            }
        }
    }

    if(count > 0) {
        averageX /= count;
        averageY /= count;

        sf::Vector2f directionToMiddle = sf::Vector2f(averageX - this->position.x, averageY - this->position.y);
        std::pair<sf::Vector2f, bool> normalizedDirectinMiddle = this->normalizeVector(directionToMiddle);
        if (normalizedDirectinMiddle.second) {
            directionToMiddle = normalizedDirectinMiddle.first * this->speed;
            this->velocity = (this->velocity * 0.998f) + (directionToMiddle * 0.002f);
            std::pair<sf::Vector2f, bool> normalizedVelocity =  this->normalizeVector(this->velocity);
            if (normalizedVelocity.second) {
                this->velocity = normalizedVelocity.first * this->speed;
            }
        }
    }
}

void Boid::checkForAttractionObstacle(std::vector<AttractionObstacle*> &attObstacles)
{
    for(auto& attObstacle : attObstacles) {
        float xDiff = attObstacle->getPosition().x - this->position.x;
        float yDiff = attObstacle->getPosition().y - this->position.y;
        auto distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));
        float weight = (1.f / (distance + 30.f));

        auto directionVector = sf::Vector2f(xDiff, yDiff);
        auto normalizedDirectionVector = this->normalizeVector(directionVector);
        if (normalizedDirectionVector.second) {
            auto directionToObstacle = normalizedDirectionVector.first * this->speed;
            this->velocity = (this->velocity * (1.0f - weight)) + (directionToObstacle * weight);
            std::pair<sf::Vector2f, bool> normalizedVelocity =  this->normalizeVector(this->velocity);
            if (normalizedVelocity.second) {
                this->velocity = normalizedVelocity.first * this->speed;
            }
        }
    }
}

std::pair<sf::Vector2f, bool> Boid::normalizeVector(sf::Vector2f vector)
{
    float vectorLength = sqrt((vector.x * vector.x) + (vector.y * vector.y));
    if (vectorLength != 0.f) {
        
        vector.x = vector.x / vectorLength;
        vector.y = vector.y / vectorLength;
        //float vectorLength = sqrt((vector.x * vector.x) + (vector.y * vector.y));
        //cout << vectorLength << endl;
        return {vector, true};
    }
    cout << vectorLength << endl;
    return {vector, false};
}

sf::Vector2f Boid::getPosition()
{
    return this->position;
}

sf::Vector2f Boid::getVelocity()
{
    return this->velocity;
}

void Boid::rotate(float vectorY, float vectorX)
{
    float rotation = atan2(vectorY, vectorX);
    this->shape.setRotation(sf::radians(rotation) + sf::radians(1.57079633));
}

