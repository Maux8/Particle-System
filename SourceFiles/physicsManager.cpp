#include "physicsManager.h"
#include "constants.h"
#include "myMath.h"

PhysicsManager::PhysicsManager(vector<unique_ptr<Particle>>& allParticlesRef)
    : particles { allParticlesRef }
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

    for (auto& particle : particles) {
        particle->update(totalForce, deltaTime);
    }
}

void PhysicsManager::computeCollision(const unsigned int i, const unsigned int j)
{
    sf::Vector2f difference = particles[j]->getPosition() - particles[i]->getPosition();
    float distance = magnitude(difference);
    float minDistance = particles[i]->getRadius() + particles[j]->getRadius();

    sf::Vector2f collisionDirection = normalize(difference);
    sf::Vector2f relativeVelocity = (particles[i]->prevPosition - particles[j]->prevPosition); // Calculate relative velocity
    float velocityAlongDirection = magnitude(project(relativeVelocity, collisionDirection)); // Project relative velocity onto collision direction

    if (velocityAlongDirection < 0)
        return; // If moving apart, no collision response needed

    float impulseScalar = RESTITUTION * velocityAlongDirection / (particles[i]->mass + particles[j]->mass);

    sf::Vector2f impulse = -impulseScalar * collisionDirection;
    particles[i]->prevPosition -= impulse / particles[i]->mass;
    particles[j]->prevPosition += impulse / particles[j]->mass;

    // Correct positions to avoid overlap
    float overlap = minDistance - distance;
    sf::Vector2f correction = collisionDirection * (overlap / 2.0f);
    particles[i]->setPosition(particles[i]->getPosition() - correction);
    particles[j]->setPosition(particles[j]->getPosition() + correction);
}

void PhysicsManager::addForce(string name, Vector2f force)
{
    allForces.insert_or_assign(name, force);
}

void PhysicsManager::remForce(string name)
{
    allForces.erase(name);
}
