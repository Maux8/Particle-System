#include <SFML/Graphics.hpp>
#include "particleManager.h"
#include "particle.h"
#include "myMath.h"

ParticleManager::ParticleManager(sf::RenderWindow& renderWindow, sf::Vector2f gravity) 
: window(renderWindow), gravity(gravity) {
    particles = std::vector<Particle>();
    forces = std::map<std::string, sf::Vector2f>();
}

void ParticleManager::addParticle(Particle particle) {
    particle.setPosition(window.getSize().x / 2, 100);
    particle.prevPosition = particle.getPosition();
    particles.push_back(particle);
    particleAmount++;
}

void ParticleManager::addForce(sf::Vector2f force, std::string name) {
    forces.insert_or_assign(name, force);
}

void ParticleManager::remForce(std::string name) {
    forces.erase(name);
}

void ParticleManager::applyForce(float deltaTime) {
    sf::Vector2f totalForce = sf::Vector2f(0.0f, 0.0f);
    for(const std::pair<const std::string, sf::Vector2f>& pair : forces) {
        totalForce += pair.second;
    }

    for(Particle& particle : particles) {
        particle.checkWindowBounds(window);
        particle.update(totalForce, deltaTime);
    }
}

void ParticleManager::applyForceTowards(sf::Vector2f point, float strength, float deltaTime) {
    for (Particle& particle : particles) {
        sf::Vector2f direction = point - particle.getPosition();
        direction = normalize(direction) * strength;
        particle.checkWindowBounds(window);
        particle.update(direction, deltaTime);
    }
}

void ParticleManager::drawParticles() {
    for (Particle& particle : particles) {
        window.draw(particle);
    }
}

