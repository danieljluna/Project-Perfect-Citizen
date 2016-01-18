#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Engine/renderSquare.h"
#include "Engine/testRenderSprite.h"
#include <iostream>
#include "Engine/testRotateSprite.h"

using namespace std;
//Note that this is placeholder for now
int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	//RenderComponent* testRect = new RenderSquare();
	//TestRenderSprite* testSprite = new TestRenderSprite("kappa.png");
	RenderComponent* testSpriteTwo = new TestRenderSprite("kappa.png");
	RenderComponent* testSpriteThree = new TestRenderSprite("kappa.png");
	sf::RenderStates testRenderState;
	//Define a Sprite
	sf::Sprite* S = new sf::Sprite();
	sf::Texture* T = new sf::Texture();
	T->loadFromFile("Kappa.png");
	S->setTexture(*T);
	S->setPosition(100, 100);
	S->setScale(0.2f, 0.2f);

	//Add the component to it
	testRotateSprite* test = new testRotateSprite(*S, 1);
    // Start the game loop
	sf::Clock deltaTime; //define deltaTime
	sf::Time dt;
    while (window.isOpen()) {
		dt = deltaTime.restart();
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
		//Update
		test->update(dt);

        // Clear screen
        window.clear();
		//testRect->render(&window);
		//going though the static renderVector inside component and calling class testRenderSprites' render function

		//TODO
		for (auto iter = RenderComponent::renderVector.begin(); iter != RenderComponent::renderVector.end(); iter++) {
			//this line casts the (*iter) which is originally a base pointer of type RenderComponent into type TestRenderSprite*
			//http://www.cplusplus.com/forum/general/2710/
			(dynamic_cast <TestRenderSprite*>(*iter))->draw(window, testRenderState);
		}

		window.draw(*S);
		//testSpriteTwo->draw(window, testRenderState);
        // Update the window
        window.display();
    }
	
	delete test;
	delete S;
	delete T;
    return EXIT_SUCCESS;
}
