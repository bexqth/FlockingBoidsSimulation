#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
protected:
    sf::Vector2f position;
    sf::CircleShape shape;
    float radius;
    float conflicArea;
public:
    Obstacle(sf::Vector2f position);
    virtual ~Obstacle();
    virtual void update() = 0;
    void draw(sf::RenderWindow& window);
    bool isMouseClicked(sf::Vector2i mousePosition);
    sf::Vector2f getPosition() const;
};

