#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Particle : public sf::CircleShape {
public:
    Vector2f prevPosition;
    bool pinned;
    float mass;

    Particle(sf::Color color, bool pinned, Vector2f posistion);

    // compute next position via verlet integration
    void update(sf::Vector2f sumOfAllForces, float deltaTime);
    void constrain(const sf::RenderWindow& window);
    void mapColorToSpeed();
    Vector2f getVelocity();
};

#endif
