#ifndef UNIVERSE_H
#define UNIVERSE_H
#include "particleManager.h"
#include "physicsManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Universe {
public:
    Universe(RenderWindow& window, Text& infoText);
    void LetThereBeLight();
    int GetParticleNumber();

private:
    Text& text;
    RenderWindow& mainWindow;
    ParticleManager particleManager;
    PhysicsManager physicsManager;
};

#endif // UNIVERSE_H
