#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Engine\renderSquare.h"
#include "Engine\testRenderSprite.h"
//Note that this is placeholder for now
int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	RenderComponent* testRect = new RenderSquare();
	TestRenderSprite* testSprite = new TestRenderSprite("kappa.png");
    // Start the game loop
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
		testRect->render(&window);
		//going though the static renderVector inside component and calling class testRenderSprites' render function
		for (auto iter = Component::renderVector.begin(); iter != Component::renderVector.end(); iter++) {
			window.draw((**iter));
		}
		//testSprite->render(&window);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
