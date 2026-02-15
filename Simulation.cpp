#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation::Simulation()
{
    this->boids.resize(40);
    this->allObstacles = {};
}

Simulation::~Simulation()
{
}

void Simulation::update(int winWidth, int winHeight)
{
    for (auto& boid : boids)
    {
        boid.checkForSeparation(boids);
    }

    for (auto& boid : boids)
    {
        boid.checkForAlignment(boids);
    }

    for (auto& boid : boids)
    {
        boid.checkForCohesion(boids);
    }
    
    for (auto& boid : boids)
    {
        boid.move(winWidth, winHeight);
    }

    for (auto& boid : boids)
    {
        boid.checkForObstacle(this->allObstacles);
    }
    
}

void Simulation::draw(sf::RenderWindow &window)
{
    for (auto& boid : boids)
    {
        boid.draw(window);
    }

    for (auto* obs : allObstacles) {
        obs->draw(window);
    }
}

void Simulation::handleMouseClick(sf::RenderWindow &window, sf::Mouse::Button button, sf::Vector2i mousePos)
{
    auto obs = this->checkIfClickedObstacle(mousePos);
    switch (button)
    {
        case sf::Mouse::Button::Right:
            cout << "RIGHT. " << endl;
            if (obs == nullptr) {
                this->allObstacles.push_back(new AttractionObstacle(sf::Vector2f(mousePos)));
            } else {
                eraseObstacle(obs);
            }
            break;
        case sf::Mouse::Button::Left:
            cout << "LEFT. " << endl;
            if (obs == nullptr) {
                this->allObstacles.push_back(new AvoidanceObstacle(sf::Vector2f(mousePos)));
            } else {
                eraseObstacle(obs);
            }
            break;    
        default:
            break;
    }
}


void Simulation::eraseObstacle(Obstacle* foundObstacle)
{
    for(int i = 0; i < this->allObstacles.size(); i++) {
        if (this->allObstacles[i] == foundObstacle) {
            this->allObstacles.erase(this->allObstacles.begin() + i);
            break;
        }
    }
    
    
}

Obstacle* Simulation::checkIfClickedObstacle(sf::Vector2i mousePos)
{
    for (auto& obs : this->allObstacles)
    {
        if (obs->isMouseClicked(mousePos))
        {
            return obs;
        }
        
    }
    
    return nullptr;
}
