#ifndef STICK_H 
#define STICK_H 
#include <SFML/Graphics.hpp>

class Stick {
    public: 
        sf::Vector2f firstPoint;
        sf::Vector2f secondPoint;
        float length;
        
        Stick(sf::Vector2f p0, sf::Vector2f p1, float length, sf::RenderWindow& window);
        void render();
    
    private:
        sf::RenderWindow& window;
};

#endif 