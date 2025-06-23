#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include "particle.h"
#include "physicsManager.h"
#include "stick.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;

class ParticleManager {

public:
    int particleAmount = 0;
    vector<unique_ptr<Particle>> particles;

    ParticleManager(RenderWindow& renderWindow, PhysicsManager& physicsMangerRef);

    void addParticle(Vector2f position);
    void remAllParticles();
    void checkCollision();
    void constrain();
    void draw();

private:
    RenderWindow& window;
    PhysicsManager& physicsManager;
};

#endif
