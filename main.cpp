#include <SFML/Graphics.hpp>
#include <sstream>
#include "particle.h"
#include "particleManager.h"
#include "myMath.h"

int main() {
    sf::Vector2f gravity = sf::Vector2f(0.0f, 1.0f);
    float mass = 1.0f;
    float pullStength = 5.0f;

    sf::RenderWindow window(sf::VideoMode(1500,900), "Particle System", sf::Style::Close);
    window.setFramerateLimit(30);
    sf::Clock clock;

    ParticleManager pm(window, gravity);
    sf::Vector2f leftPoint(150, window.getSize().y / 2);
    sf::Vector2f rightPoint(window.getSize().x - 150, window.getSize().y / 2);
    sf::Vector2f centerPoint(window.getSize().x / 2, window.getSize().y / 2);

    sf::Font font;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(window.getSize().x - 200, 50);

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        return -1;
    }

    while (window.isOpen()) {

        sf::Event event;
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                //spacebar to spawn particles
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    Particle particle(20.0f, mass, sf::Color::White);
                    pm.addParticle(particle);
                }   
                // a to apply left force
                else if(event.key.scancode == sf::Keyboard::Scan::A) {
                    pm.applyForceTowards(leftPoint, pullStength, deltaTime);
                }
                // d tp apply right force
                else if(event.key.scancode == sf::Keyboard::Scan::D) {
                    pm.applyForceTowards(rightPoint, pullStength, deltaTime);
                }
                // s tp apply center force
                else if(event.key.scancode == sf::Keyboard::Scan::S) {
                    pm.applyForceTowards(centerPoint, pullStength, deltaTime);
                }
                
            }
        }

        window.clear();

        pm.applyForce(deltaTime);
        pm.drawParticles();

        std::stringstream ss;
        ss << "Particles: " << pm.particleAmount;
        text.setString(ss.str());
        window.draw(text);

        window.display();
        
    }

    return 0;
}