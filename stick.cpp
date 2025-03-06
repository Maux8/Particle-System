#include "stick.h"
#include <array>

Stick::Stick(sf::Vector2f p0, sf::Vector2f p1, float length, sf::RenderWindow& renderWindow)
: window(renderWindow) {
    this->firstPoint = p0;
    this->secondPoint = p1;
    this->length = length;
}

void Stick::render() { 
    std::array line = {
        sf::Vertex{this->firstPoint},
        sf::Vertex{this->secondPoint}
    };

    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}