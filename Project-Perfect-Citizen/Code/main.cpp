//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath()
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Engine/testRenderSprite.h"
#include <iostream>
#include "Engine/testRotateSprite.h"
#include "Engine/subject.h"
#include "Engine/TestSubject.h"
#include "Engine/TestObserver.h"
#include "Engine/debug.h"

using namespace ppc;


//Note that this is placeholder for now
int main(int argc, char** argv) {
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	//Example of using the debugger macro
	DEBUGF("ac", argc);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    //Create A TestRenderSprite
	TestRenderSprite testSpriteTwo(resourcePath() + "kappa.png");

	//Define a Sprite
	sf::Sprite S;
	sf::Texture T;
	T.loadFromFile(resourcePath() + "kappa.png");
	S.setTexture(T);
	S.setPosition(100, 100);
	S.setScale(0.2f, 0.2f);

////Start the game loop
    //Used to keep track time
	sf::Clock deltaTime;
    //Marks the times since the last frame
	sf::Time dt;
    while (window.isOpen()) {
        //Save the new dt
		dt = deltaTime.restart();

        //Process sf::events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        //Draw Objects
		window.draw(S);
		
        //Display final Window
        window.display();
    }
    return EXIT_SUCCESS;
}
