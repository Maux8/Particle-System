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

        void addForce(sf::Vector2f force, std::string name);
        void remForce(std::string name);

        void applyForce(float deltaTime);

        void applyForceTowards(sf::Vector2f point, float strength, float deltaTime);

        void drawParticles();
    
    private:
        sf::RenderWindow& window;
};

#endif