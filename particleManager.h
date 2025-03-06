#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "particle.h"
#include "stick.h"

class ParticleManager {

    public:
        int particleAmount = 0; 
        sf::Vector2f gravity;
        std::vector<std::shared_ptr<Particle>> particles;
        std::vector<std::unique_ptr<Stick>> sticks;
        std::map<std::string, sf::Vector2f> forces;
        
        ParticleManager(sf::RenderWindow& window, sf::Vector2f gravity);

        void addStick(std::unique_ptr<Stick> stick);
        void remAllSticks();

        std::shared_ptr<Particle> addParticle(std::shared_ptr<Particle> particle);
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

        void spawnRectangleWithAnchor(float mass, float radius);

        void draw();
    
    private:
        sf::RenderWindow& window;
};

#endif