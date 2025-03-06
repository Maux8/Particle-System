#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle : public sf::CircleShape {
    
    public:
        sf::Vector2f prevPosition;
        bool pinned;
        float mass;
        
        Particle(float radius, float mass, sf::Color color, bool pinned, float x, float y);

        /// @brief compute next position via verlet integration
        /// @param sumOfAllForces 
        /// @param deltaTime 
        void update(sf::Vector2f sumOfAllForces, float deltaTime);
        void constrain(const sf::RenderWindow& window);


};

#endif