#include <SFML/Graphics.hpp>
#include <sstream>
#include "particle.h"
#include "particleManager.h"
#include "myMath.h"

int main() {
    sf::Vector2f gravity = sf::Vector2f(0.0f, 100.0f);
    float mass = 1.0f;
    float pullStength = 150.0f;
    float radius = 20.0f;
    bool leftForceOn = false;
    bool rightForceOn = false;

    sf::RenderWindow window(sf::VideoMode(1500,900), "Particle System", sf::Style::Close);
    window.setFramerateLimit(120);
    sf::Clock clock;

    ParticleManager pm(window, gravity);
    pm.addForce(gravity, "gravity");
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
                    Particle particle(radius, mass, sf::Color::White);
                    particle.setOrigin(radius, radius);
                    pm.addParticle(particle);
                }   
                // a to turn on left force
                else if (event.key.scancode == sf::Keyboard::Scan::A && !leftForceOn) {
                    leftForceOn = true;
                    sf::Vector2f force = sf::Vector2f(-pullStength, 0);
                    pm.addForce(force, "leftForce");
                }
                // d to turn on right force
                else if (event.key.scancode == sf::Keyboard::Scan::D && !rightForceOn) {
                    rightForceOn = true;
                    sf::Vector2f force = sf::Vector2f(pullStength, 0);
                    pm.addForce(force, "rightForce");
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // release a to turn off left force
                if (event.key.scancode == sf::Keyboard::Scan::A && leftForceOn) {
                    leftForceOn = false;
                    pm.remForce("leftForce");
                }
                // release d to turn off right force
                else if (event.key.scancode == sf::Keyboard::Scan::D && rightForceOn) {
                    rightForceOn = false;
                    pm.remForce("rightForce");
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