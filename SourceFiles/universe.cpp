#include "universe.h"
#include <sstream>

Universe::Universe(RenderWindow& windowRef, Text& textRef)
    : mainWindow(windowRef)
    , text(textRef)
    , particleManager(windowRef, physicsManager)
    , physicsManager(particleManager.particles)
{
}

void Universe::LetThereBeLight()
{
    while (mainWindow.isOpen()) {
        mainWindow.clear();
        physicsManager.deltaTime = physicsManager.time.restart().asSeconds();
        Event event;

        // do all events that came in
        while (mainWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                mainWindow.close();
            }

            if (event.type == Event::KeyPressed) {
                // spacebar to spawn particles
                if (event.key.scancode == Keyboard::Scan::Space) {
                    particleManager.addParticle(Vector2f(mainWindow.getSize().x / 2, 100));
                    // R to delete all particles
                } else if (event.key.scancode == Keyboard::Scan::R) {
                    particleManager.remAllParticles();
                }
            } else if (event.type == Event::KeyReleased) {
                // release Q to close the window
                if (event.key.scancode == Keyboard::Scan::Q) {
                    mainWindow.close();
                }
            } else if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePos = Mouse::getPosition(mainWindow);
                Vector2f mousePosFloat = Vector2f((float)mousePos.x, (float)mousePos.y);
                particleManager.addParticle(mousePosFloat);
            }
        }
        // events finished

        physicsManager.updateParticles();
        particleManager.checkCollision();
        particleManager.constrain();
        particleManager.draw();

        std::stringstream ss;
        ss << "Particles: " << particleManager.particleAmount;
        text.setString(ss.str());
        mainWindow.draw(text);
        mainWindow.display();
    }
}

int Universe::GetParticleNumber()
{
    return particleManager.particleAmount;
}
