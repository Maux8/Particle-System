#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "constants.h"
#include "particle.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;

class PhysicsManager {
public:
    Clock time;
    float deltaTime;
    PhysicsManager(vector<unique_ptr<Particle>>& allPartilcesRef);
    void addForce(string name, Vector2f force);
    void remForce(string name);
    void updateParticles();
    void computeCollision(unique_ptr<Particle>& firstParticle,
        unique_ptr<Particle>& secondParticle);

private:
    map<std::string, sf::Vector2f> allForces;
    vector<unique_ptr<Particle>>& allParticles;
};

#endif // PHYSICSMANAGER_H
