#pragma once
#include <SFML/Graphics.hpp>

class Boid
{
    private:
        float radius;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        sf::CircleShape shape;
    public:
        Boid();
        ~Boid();
        void update();
        void draw(sf::RenderWindow& window);
        void move();
};

