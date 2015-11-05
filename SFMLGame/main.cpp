#include <iostream>

#include <SFML/Graphics.hpp>

#include "Helios/helios_main.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::Texture tex_bat;
    if (!tex_bat.loadFromFile("Resources/Images/bat.png")) {
        std::cerr << "Could not load bat.png!" << std::endl;
        system("PAUSE");
        window.close();
    }
    tex_bat.setSmooth(true);
    tex_bat.setRepeated(true);
    sf::Sprite spr_bat;
    spr_bat.setTexture(tex_bat);
    spr_bat.setOrigin(sf::Vector2f(8, 36));
    spr_bat.setPosition(sf::Vector2f(10, 50));

    Helios::Room testing(window.getSize());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(testing);
        window.display();
    }

    return 0;
}

