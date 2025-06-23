#include "physicsManager.h"
#include "constants.h"
#include "myMath.h"

PhysicsManager::PhysicsManager(vector<unique_ptr<Particle>>& allParticlesRef)
    : allParticles { allParticlesRef }
{
    allForces = std::map<std::string, sf::Vector2f>();
    // init gravity going down
    Vector2f Gravity = Vector2f(0.0f, GRAVITY_STRENGTH * GRAVITY_BOOST);
    this->addForce("gravity", Gravity);
}

void PhysicsManager::updateParticles()
{
    sf::Vector2f totalForce = sf::Vector2f(0.0f, 0.0f);
    for (const std::pair<const std::string&, sf::Vector2f>& pair : allForces) {
        totalForce += pair.second;
    }

    for (auto& particle : allParticles) {
        particle->update(totalForce, deltaTime);
    }
}

void PhysicsManager::computeCollision(unique_ptr<Particle>& firstParticle,
    unique_ptr<Particle>& secondParticle)
{
    Vector2f difference = secondParticle->getPosition() - firstParticle->getPosition();
    float distance = magnitude(difference);
    float minDistance = firstParticle->getRadius() + secondParticle->getRadius();

    sf::Vector2f collisionDirection = normalize(difference);
    sf::Vector2f relativeVelocity = (firstParticle->prevPosition - secondParticle->prevPosition); // Calculate relative velocity
    float velocityAlongDirection = magnitude(project(relativeVelocity, collisionDirection)); // Project relative velocity onto collision direction

    if (velocityAlongDirection < 0)
        return; // If moving apart, no collision response needed

    float impulseScalar = 1.0f * velocityAlongDirection / (firstParticle->mass + secondParticle->mass);

    sf::Vector2f impulse = -impulseScalar * collisionDirection;
    firstParticle->prevPosition -= impulse / firstParticle->mass;
    secondParticle->prevPosition += impulse / secondParticle->mass;

    // Correct positions to avoid overlap
    float overlap = minDistance - distance;
    sf::Vector2f correction = collisionDirection * (overlap / 2.0f);
    firstParticle->setPosition(firstParticle->getPosition() - correction);
    firstParticle->setPosition(firstParticle->getPosition() + correction);
}

void PhysicsManager::addForce(string name, Vector2f force)
{
    allForces.insert_or_assign(name, force);
}

void PhysicsManager::remForce(string name)
{
    allForces.erase(name);
}
