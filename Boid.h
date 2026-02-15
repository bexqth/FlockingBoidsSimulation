#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "AttractionObstacle.h"
#include "AvoidanceObstacle.h"

class Boid
{
    private:
        float radius;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::CircleShape shape;
        float speed;
    public:
        Boid();
        ~Boid();
        void update();
        void draw(sf::RenderWindow& window);
        void move(int maxWidth, int maxHeight);
        void checkWindowBorders(int maxWidth, int maxHeight);
        void checkForSeparation(std::vector<Boid>& vector);
        void checkForAlignment(std::vector<Boid>& vector);
        void checkForCohesion(std::vector<Boid>& vector);
        void checkForObstacle(std::vector<Obstacle*>& obstacles);
        std::pair<sf::Vector2f, bool> normalizeVector(sf::Vector2f vector);
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        void rotate(float vectorY, float vectorX);
};

