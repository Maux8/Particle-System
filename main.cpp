#include <SFML/Graphics.hpp>
#include <sstream>
#include "particle.h"
#include "particleManager.h"
#include "myMath.h"
#include "stick.h"

int main() {
    sf::Vector2f gravity = sf::Vector2f(0.0f, 300.0f);
    float mass = 1.0f;
    float sideStength = 200.0f;
    float centerStrength = 1000.0f;
    float radius = 30.0f;
    bool leftForceOn = false;
    bool rightForceOn = false;

    sf::RenderWindow window(sf::VideoMode(2000,1500), "Particle System", sf::Style::Close);
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
                    auto particle = std::make_shared<Particle>(radius, mass, sf::Color::White, false, window.getSize().x / 2, 100);
                    pm.addParticle(particle);
                }   
                // a to turn on left force
                else if (event.key.scancode == sf::Keyboard::Scan::A && !leftForceOn) {
                    leftForceOn = true;
                    sf::Vector2f force = sf::Vector2f(-sideStength, 0);
                    pm.addForce(force, "leftForce");
                }
                // d to turn on right force
                else if (event.key.scancode == sf::Keyboard::Scan::D && !rightForceOn) {
                    rightForceOn = true;
                    sf::Vector2f force = sf::Vector2f(sideStength, 0);
                    pm.addForce(force, "rightForce");
                }
                // s to turn on center force
                else if(event.key.scancode == sf::Keyboard::Scan::S) {
                    pm.applyForceTowards(centerPoint, centerStrength, deltaTime);
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
                // release r to remove all particles and sticks
                else if (event.key.scancode == sf::Keyboard::Scan::R) {
                    pm.remAllParticles();
                    pm.remAllSticks();
                }
                // release q to close the window
                else if (event.key.scancode == sf::Keyboard::Scan::Q) {
                    window.close();
                }
                // release w to spawn to particles with a stick between them 
                else if (event.key.scancode == sf::Keyboard::Scan::W)  {

                    auto particle1 = std::make_shared<Particle>(radius, mass, sf::Color::White, false, window.getSize().x / 2, 100);
                    auto particle2 = std::make_shared<Particle>(radius, mass, sf::Color::White, false, window.getSize().x / 2 + 300, 400);
                    pm.addParticle(particle1);
                    pm.addParticle(particle2);
                    auto stick = std::make_unique<Stick>(particle1, particle2, 300, window);
                    pm.addStick(std::move(stick));
                }
                // release T to spawn a rectangle with anchor
                else if (event.key.scancode == sf::Keyboard::Scan::T) {
                    pm.spawnRectangleWithAnchor(mass, radius);
                }
            }
        }

        window.clear();

        pm.applyForce(deltaTime);
        pm.draw();
        
        std::stringstream ss;
        ss << "Particles: " << pm.particleAmount;
        text.setString(ss.str());
        window.draw(text);

        window.display();
        
    }

    return 0;
}