#include "stick.h"
#include "particle.h"
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
    // Update logic for the stick
}