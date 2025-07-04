#include "particle.h"
#include "constants.h"
#include "myMath.h"

Particle::Particle(sf::Color color, bool pinned, Vector2f positionToSpawn)
    : sf::CircleShape(PARTICLE_RADIUS)
{
    this->setPosition(positionToSpawn);
    this->mass = PARTICLE_MASS;
    this->pinned = pinned;
    this->setFillColor(color);
}

void Particle::update(sf::Vector2f sumOfAllForces, float deltaTime)
{
    if (!this->pinned) {
        sf::Vector2f position = this->getPosition();
        sf::Vector2f acceleration = sumOfAllForces / this->mass;
        sf::Vector2f velocity = this->getPosition() - this->prevPosition;
        this->prevPosition = this->getPosition();
        this->setPosition(this->getPosition() + velocity + acceleration * deltaTime * deltaTime);
        mapColorToSpeed();
    }
}

void Particle::constrain(const sf::RenderWindow& window)
{
    sf::Vector2f position = this->getPosition();
    sf::Vector2f velocity = position - this->prevPosition;
    float radius = this->getRadius();

    if (position.x - radius < 0) {
        this->setPosition(0 + radius, position.y);
        this->prevPosition.x = this->getPosition().x + velocity.x * RESTITUTION;
    } else if (position.x + radius > window.getSize().x) {
        this->setPosition(window.getSize().x - radius, position.y);
        this->prevPosition.x = this->getPosition().x + velocity.x * RESTITUTION;
    } else if (position.y - radius < 0) {
        this->setPosition(position.x, 0 + radius);
        this->prevPosition.y = this->getPosition().y + velocity.y * RESTITUTION;
    } else if (position.y + radius > window.getSize().y) {
        this->setPosition(position.x, window.getSize().y - radius);
        position = this->getPosition();
        this->prevPosition.y = this->getPosition().y + velocity.y * RESTITUTION;
    }
}

void Particle::mapColorToSpeed()
{
    Vector2f velocity = this->getVelocity();
    float speed = magnitude(velocity);
    float maxSpeed = 10.0f;
    float relation = speed / maxSpeed;

    if (relation > 1.0f)
        relation = 1.0f;

    float a = -255;
    float b = 255;
    float result = a * relation + b;

    if (result > 255)
        result = 255;
    else if (result < 0)
        result = 0;

    Uint8 red = 255;
    Uint8 green = static_cast<sf::Uint8>(result);
    Uint8 blue = green;

    Color colorToSet = Color(red, green, blue);

    this->setFillColor(colorToSet);
}

Vector2f Particle::getVelocity()
{
    return this->getPosition() - this->prevPosition;
}
