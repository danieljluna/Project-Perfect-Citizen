#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Helios/helios_main.h"

#include "aoe_unit.h"


void LoadTexture(sf::Texture &texture, 
                 const std::string& filename, 
                 const sf::IntRect area = sf::IntRect());

void Init(const std::string& filename);

int main() {
    try {
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

        sf::Texture MyTexture;
        LoadTexture(MyTexture, "Resources/Images/StickUnit.png");
        MyTexture.setSmooth(true);

        sf::Sprite unitStatic(MyTexture);
        unitStatic.setPosition(sf::Vector2f(10,10));
        helios::Animation anim(1, unitStatic);

        aoe::Unit::defaultAnimations.push_back(anim);

        helios::Room testing(window.getSize());
        aoe::Unit unit(0);
        unit.Activate(&testing);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color(128,0,0));
            unit.Update();
            window.draw(testing);
            window.display();
        }

        return 0;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::system("PAUSE");
        std::exit(EXIT_FAILURE);
    }
}




void LoadTexture(sf::Texture &texture, 
                 const std::string& filename, 
                 const sf::IntRect area) {
    if (!texture.loadFromFile(filename, area)) {
        std::string msg = "The file " + filename + 
                " could not be loaded!";
        throw std::runtime_error(msg);
    } else {
        std::cout << filename << " successfully loaded!" << std::endl;
    }
}

