#include "particle.h"
#include "myMath.h"

Particle::Particle(float radius, float mass, sf::Color color) 
: sf::CircleShape(radius) {
    this->mass = mass;
    this->setFillColor(color);
}

void Particle::update(sf::Vector2f sumOfAllForces, float deltaTime) {
    sf::Vector2f position = this->getPosition();
    sf::Vector2f acceleration = sumOfAllForces / this->mass;
    sf::Vector2f velocity = this->getPosition() - this->prevPosition;
    this->prevPosition = this->getPosition();
    this->setPosition(this->getPosition() + velocity + acceleration * deltaTime * deltaTime);
}

void Particle::checkWindowBounds(const sf::RenderWindow& window, sf::Vector2f& gravity) {
    
}