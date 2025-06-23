#include "stick.h"
#include "particle.h"
#include "myMath.h"
#include <array>

Stick::Stick(std::shared_ptr<Particle> p0, std::shared_ptr<Particle> p1, float length, sf::RenderWindow& renderWindow)
: window(renderWindow), firstPoint(p0), secondPoint(p1), length(length) {
}

void Stick::render() { 
    std::array line = {
        sf::Vertex{this->firstPoint->getPosition()},
        sf::Vertex{this->secondPoint->getPosition()}
    };

    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void Stick::update(float deltaTime) {
    sf::Vector2f delta = secondPoint->getPosition() - firstPoint->getPosition();
    float distance = distanceBetween(secondPoint->getPosition(), firstPoint->getPosition());
    float difference = this->length - distance;
    float percent = (difference / distance) / 2;

    sf::Vector2f offset = delta * percent;

    if (!firstPoint->pinned) {
        this->firstPoint->move(-offset);
    }
    if (!secondPoint->pinned) {
        this->secondPoint->move(offset);
    }
}