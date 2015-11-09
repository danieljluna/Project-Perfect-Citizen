#include <iostream>
#include <vector>
#include <exception>

#include <SFML/Graphics.hpp>

#include "Helios/helios_main.h"

#include "aoe_unit.h"



std::vector<sf::Sprite> constructAnimation() {

};

int main() {
    try {
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

        helios::Room testing(window.getSize());
        aoe::Unit unit(0);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            unit.Update();
            window.draw(unit);
            window.display();
        }

        return 0;
    } catch (std::exception &e) {

    }
}

