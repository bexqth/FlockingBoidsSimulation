#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation::Simulation()
{
    this->boids.resize(40);
    this->attractionObstacles = {};
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
        boid.checkForAttractionObstacle(this->attractionObstacles);
    }
    
}

void Simulation::draw(sf::RenderWindow &window)
{
    for (auto& boid : boids)
    {
        boid.draw(window);
    }

    for (auto* obs : attractionObstacles) {
        obs->draw(window);
    }
}

void Simulation::handleMouseClick(sf::RenderWindow &window, sf::Mouse::Button button, sf::Vector2i mousePos)
{
    switch (button)
    {
        case sf::Mouse::Button::Right:
            auto obs = this->checkIfClickedObstacle(mousePos);
            //cout << obs << endl;
            if (obs == nullptr) {
                this->attractionObstacles.push_back(new AttractionObstacle(sf::Vector2f(mousePos)));
            } else {
                eraseObstacle(obs);
            }
            break;
    }
}


void Simulation::eraseObstacle(Obstacle* foundObstacle)
{
    for(int i = 0; i < this->attractionObstacles.size(); i++) {
        if (this->attractionObstacles[i] == foundObstacle) {
            this->attractionObstacles.erase(this->attractionObstacles.begin() + i);
            break;
        }
    }
}

Obstacle* Simulation::checkIfClickedObstacle(sf::Vector2i mousePos)
{
    for (auto& atObs : this->attractionObstacles)
    {
        if (atObs->isMouseClicked(mousePos))
        {
            return atObs;
        }
        
    }
    return nullptr;
}
