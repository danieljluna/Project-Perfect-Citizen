#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine\testMoveSpriteCircular.h"

using namespace std;
//Note that this is placeholder for now
int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	//Define a Sprite
	sf::Sprite* S = new sf::Sprite();
	sf::Texture* T = new sf::Texture();
	T->loadFromFile("Kappa.png");
	S->setTexture(*T);
	S->setPosition(100, 100);
	S->setScale(0.2f, 0.2f);

	//Add the component to it
	float angularVelocity = 10.0f;
	sf::Vector2f wndCenter(400.0f, 300.0f);
	//testMoveSpriteCircular* test = new testMoveSpriteCircular(*S, wndCenter, angularVelocity);
	testMoveSpriteCircular test(S, wndCenter, angularVelocity);
    // Start the game loop
	sf::Clock deltaTime; //define deltaTime
	sf::Time dt;
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
		//Update before draw/render
		test.update(dt);
		window.draw(*S);
        // Update the window
        window.display();

		dt = deltaTime.restart();
    }
    return EXIT_SUCCESS;
}
