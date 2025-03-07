#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include "particleManager.h"
#include "particle.h"
#include "stick.h"
#include "myMath.h"

ParticleManager::ParticleManager(sf::RenderWindow& renderWindow, sf::Vector2f gravity) 
: window(renderWindow), gravity(gravity) {
    particles = std::vector<std::shared_ptr<Particle>>();
    forces = std::map<std::string, sf::Vector2f>();
}

void ParticleManager::addStick(std::unique_ptr<Stick> stick) {
    sticks.push_back(std::move(stick));
}

void ParticleManager::remAllSticks() {
    sticks.clear();
}

std::shared_ptr<Particle> ParticleManager::addParticle(std::shared_ptr<Particle> particle) {
    particle->setOrigin(particle->getRadius(), particle->getRadius());
    particle->prevPosition = particle->getPosition();
    particles.push_back(particle);
    particleAmount++;
    return particles.back();
}

void ParticleManager::remAllParticles() {
    particles.clear();
    particleAmount = 0;
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

    for(auto& stick : sticks) {
        stick->update(deltaTime);
    }

    for(auto& particle : particles) {
        particle->constrain(window);
        particle->update(totalForce, deltaTime);
    }
    // uncommont this line to activate collision detection
    checkCollision(deltaTime);
}

void ParticleManager::applyForceTowards(sf::Vector2f point, float strength, float deltaTime) {
    for (auto& particle : particles) {
        sf::Vector2f direction = point - particle->getPosition();
        direction = normalize(direction) * strength;
        particle->constrain(window);
        particle->update(direction, deltaTime);
    }
}

void ParticleManager::checkCollision(float deltaTime) {
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i + 1; j < particles.size(); ++j) {
            sf::Vector2f difference = particles[j]->getPosition() - particles[i]->getPosition();
            float distance = magnitude(difference);
            float minDistance = particles[i]->getRadius() + particles[j]->getRadius();

            if (distance < minDistance) {
                sf::Vector2f collisionDirection = normalize(difference);
                sf::Vector2f relativeVelocity = (particles[i]->prevPosition - particles[j]->prevPosition); // Calculate relative velocity
                float velocityAlongDirection = magnitude(project(relativeVelocity, collisionDirection)); // Project relative velocity onto collision direction

                if (velocityAlongDirection < 0) return; // If moving apart, no collision response needed

                float restitution = 1.0f; // Coefficient of restitution 
                float impulseScalar = restitution * velocityAlongDirection / (particles[i]->mass + particles[j]->mass);

                sf::Vector2f impulse = -impulseScalar * collisionDirection;
                particles[i]->prevPosition -= impulse / particles[i]->mass;
                particles[j]->prevPosition += impulse / particles[j]->mass;

                // Correct positions to avoid overlap
                float overlap = minDistance - distance;
                sf::Vector2f correction = collisionDirection * (overlap / 2.0f);
                particles[i]->setPosition(particles[i]->getPosition() - correction);
                particles[j]->setPosition(particles[j]->getPosition() + correction);
            }
        }
    }
}

void ParticleManager::spawnRectangleWithAnchor(float mass, float radius) {
    std::array _particles = {
        std::make_shared<Particle>(radius, mass, sf::Color::White, false, 200, 200),                    // A
        std::make_shared<Particle>(radius, mass, sf::Color::White, false, 500, 200),                    // B
        std::make_shared<Particle>(radius, mass, sf::Color::White, false, 500, 500),                    // C
        std::make_shared<Particle>(radius, mass, sf::Color::White, false, 200, 500),                    // D
        std::make_shared<Particle>(radius, mass, sf::Color::White, true, window.getSize().x / 2, 50)    // Anchor
    };

    std::array _sticks = {
        std::make_unique<Stick>(_particles[0], _particles[1], 300.0f, window),          // A to B
        std::make_unique<Stick>(_particles[1], _particles[2], 300.0f, window),          // B to C
        std::make_unique<Stick>(_particles[2], _particles[3], 300.0f, window),          // C to D
        std::make_unique<Stick>(_particles[3], _particles[0], 300.0f, window),          // D to A
        std::make_unique<Stick>(_particles[0], _particles[2], 424.264068712f, window),  // A to C
        std::make_unique<Stick>(_particles[1], _particles[4], 700.0f, window),          // B to Anchor
    };

    for (auto& particle : _particles) {
        this->addParticle(particle);
    }

    for (auto& stick : _sticks) {
        this->addStick(std::move(stick));
    }
}

void ParticleManager::draw() {
    for(auto& stick : sticks) {
        stick->render();
    }

    for(auto& particle : particles) {
        window.draw(*particle);
    }

}

