#include "particleManager.h"
#include "myMath.h"
#include "particle.h"
#include "physicsManager.h"
#include "stick.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <memory>
#include <vector>

ParticleManager::ParticleManager(sf::RenderWindow& renderWindow, PhysicsManager& physicsManagerRef)
    : window(renderWindow)
    , physicsManager(physicsManagerRef)
{
    particles = vector<unique_ptr<Particle>>();
}

void ParticleManager::addParticle(Vector2f position)
{
    Vector2f realPosition(position.x, position.y - 100);
    auto particle = make_unique<Particle>(Color::White, false, realPosition);
    particle->setOrigin(particle->getRadius(), particle->getRadius());
    particle->prevPosition = particle->getPosition();
    particles.push_back(std::move(particle));
    particleAmount++;
}

void ParticleManager::remAllParticles()
{
    particles.clear();
    particleAmount = 0;
}

void ParticleManager::checkCollision()
{
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i + 1; j < particles.size(); ++j) {
            sf::Vector2f difference = particles[j]->getPosition() - particles[i]->getPosition();
            float distance = magnitude(difference);
            float minDistance = particles[i]->getRadius() + particles[j]->getRadius();

            if (distance < minDistance) {
                physicsManager.computeCollision(particles[i], particles[j]);
            }
        }
    }
}

void ParticleManager::constrain()
{
    for (auto& particle : particles) {
        particle->constrain(window);
    }
}

void ParticleManager::draw()
{
    for (auto& particle : particles) {
        window.draw(*particle);
    }
}

// void ParticleManager::applyForceTowards(sf::Vector2f point, float strength, float deltaTime)
// {
//     for (auto& particle : particles) {
//         sf::Vector2f direction = point - particle->getPosition();
//         direction = normalize(direction) * strength;
//         particle->constrain(window);
//         particle->update(direction, deltaTime);
//     }
// }
