#include "universe.h"

#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(2500, 1500), "Particle System", Style::Close);
    window.setFramerateLimit(120);
    Text text;
    Universe universe = Universe(window, text);

    Font font;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(window.getSize().x - 200, 50);

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        return -1;
    }

    // lets go
    universe.LetThereBeLight();

    return 0;
}
