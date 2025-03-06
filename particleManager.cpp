#include <SFML/Graphics.hpp>
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
    particle->setPosition(window.getSize().x / 2, 100);
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
    //checkCollision(deltaTime);
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
                sf::Vector2f relativeVelocity = (particles[i]->prevPosition - particles[j]->prevPosition);
                float velocityAlongDirection = dot(relativeVelocity, collisionDirection);

                if (velocityAlongDirection > 0) return;

                float restitution = 0.5f; // Coefficient of restitution (elastic collision)
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

void ParticleManager::draw() {
    for(auto& stick : sticks) {
        stick->render();
    }

    for(auto& particle : particles) {
        window.draw(*particle);
    }

}

