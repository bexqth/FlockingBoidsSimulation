#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Boid
{
    private:
        float radius;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        sf::CircleShape shape;
        float speed;
    public:
        Boid();
        ~Boid();
        void update();
        void draw(sf::RenderWindow& window);
        void move();
        void checkForSeparation(std::vector<Boid>& vector);
        void checkForAlignment(std::vector<Boid>& vector);
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        void rotate(float vectorY, float vectorX);
};

