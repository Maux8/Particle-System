#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle : public sf::CircleShape {
    
    public:
        sf::Vector2f prevPosition;

        float mass;
        
        Particle(float radius, float mass, sf::Color color);

        // compute next position via verlet integration
        void update(sf::Vector2f sumOfAllForces, float deltaTime);
        void checkWindowBounds(const sf::RenderWindow& window);


};

#endif