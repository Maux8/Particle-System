#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "particle.h"

class ParticleManager {

    public:
        int particleAmount = 0; 
        sf::Vector2f gravity;
        std::vector<Particle> particles;
        std::map<std::string, sf::Vector2f> forces;
        
        ParticleManager(sf::RenderWindow& window, sf::Vector2f gravity);

        void addParticle(Particle particle);

        void remAllParticles();

        void addForce(sf::Vector2f force, std::string name);

        void remForce(std::string name);

        /// @brief apply general force to all particles
        /// @param deltaTime 
        void applyForce(float deltaTime);

        /// @brief apply specific force towards a specific point to all particles
        /// @param point 
        /// @param strength 
        /// @param deltaTime 
        void applyForceTowards(sf::Vector2f point, float strength, float deltaTime);

        /// @brief checks for collisions between particles
        /// @param deltatTime 
        void checkCollision(float deltatTime);

        void drawParticles();
    
    private:
        sf::RenderWindow& window;
};

#endif