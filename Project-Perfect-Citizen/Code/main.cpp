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
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML window");
	sf::Mouse myMouse;
	sf::Vector2i mouse_position;
	mouse_position = sf::Mouse::getPosition(window);

	ppc::Window myWindow (200.0f, 250.0f, 50.0f, 50.0f);
	ppc::Window myWindow2(100.0f, 100.0f, 300.0f, 50.0f);


    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseMoved) 
			{
				mouse_position.x = event.mouseMove.x;
				mouse_position.y = event.mouseMove.y;
			}
        }
		
        // Clear screen
        window.clear();

		//if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		if (event.type == sf::Event::MouseMoved)
		{
			if (myMouse.isButtonPressed(sf::Mouse::Left))
			{
			
				if (myWindow.intersectsMouse(mouse_position))
					myWindow.setPosition(mouse_position.x-10, mouse_position.y-10);
				if (myWindow2.intersectsMouse(mouse_position))
					myWindow2.setPosition(mouse_position.x-10, mouse_position.y-10);
			}
		}
        // Update the window
		window.draw(myWindow);
		window.draw(myWindow2);
        window.display();
    }
    return EXIT_SUCCESS;
}
