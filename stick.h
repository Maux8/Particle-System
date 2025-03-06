#ifndef STICK_H 
#define STICK_H 
#include <SFML/Graphics.hpp>
#include "particle.h"
#include <memory>

class Stick {
    public: 
        std::shared_ptr<Particle> firstPoint;
        std::shared_ptr<Particle> secondPoint;
        float length;

        Stick(std::shared_ptr<Particle> p0, std::shared_ptr<Particle> p1, float length, sf::RenderWindow& window);
        void render();
        void update(float deltaTime);
    
    private:
        sf::RenderWindow& window;
};

#endif