#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Engine/ppc_window.h"

//Note that this is placeholder for now
int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	sf::Vector2i mouse_position;
	mouse_position = sf::Mouse::getPosition(window);

	ppc::Window myWindow (200.0f, 250.0f);



    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				mouse_position.x = event.mouseButton.x;
				mouse_position.y = event.mouseButton.y;
			}
        }
		
        // Clear screen
        window.clear();

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			myWindow.setPosition(mouse_position.x, mouse_position.y);
		}
        // Update the window
		window.draw(myWindow);
        window.display();
    }
    return EXIT_SUCCESS;
}
