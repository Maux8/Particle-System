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

void Particle::checkWindowBounds(const sf::RenderWindow& window) {
    float restituion = 0.9f;
    sf::Vector2f position = this->getPosition();
    sf::Vector2f velocity = position - this->prevPosition;
    float radius = this->getRadius();
    
    if (position.x - radius < 0) {
        this->setPosition(0 + radius, position.y);
        this->prevPosition.x = this->getPosition().x + velocity.x * restituion; 
    }
    else if (position.x + radius > window.getSize().x) {
        this->setPosition(window.getSize().x - radius, position.y);
        this->prevPosition.x = this->getPosition().x + velocity.x * restituion;
    }
    else if (position.y - radius < 0) {
        this->setPosition(position.x, 0 + radius);
        this->prevPosition.y = this->getPosition().y + velocity.y * restituion;
    }
    else if (position.y + radius > window.getSize().y) {
        this->setPosition(position.x, window.getSize().y - radius);
        position = this->getPosition();
        this->prevPosition.y = this->getPosition().y + velocity.y * restituion;
    } 
}

