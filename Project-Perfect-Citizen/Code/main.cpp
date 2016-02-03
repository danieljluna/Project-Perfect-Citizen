//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath() string()
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <iostream>

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Engine/testRenderSprite.h"
#include "Engine/testRotateSprite.h"
#include "Engine/TestSubject.h"
#include "Engine/TestObserver.h"
#include "Engine/debug.h"
#include "Engine/entity.h"
#include "Engine/Window.h"
#include "Engine/desktop.h"

using namespace ppc;


//Note that this is placeholder for now
int main(int argc, char** argv) {
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	//Example of using the debugger macro
	DEBUGF("ac", argc);

    // Create the main sf::window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    //Define a Sprite
    sf::Sprite S;
    sf::Texture T;
    if (!(T.loadFromFile(resourcePath() + "Resources/kappa.png"))) {
        //Test for failure
        cerr << "COULD NOT LOAD KAPPA.PNG\n";
        std::system("PAUSE");
        return -1;
    };
    S.setTexture(T);
    S.setPosition(300, 300);
    S.setScale(0.2f, 0.2f);


    //Create A TestRenderSprite
    TestRenderSprite testRenderSpr(resourcePath() + "Resources/kappa.png");

    //Create A TestRotateSprite
	testRotateSprite testSprCmpnt;
    
    //Put that Component into an Entity
    Entity testEntity;
    testEntity.addComponent(&testRenderSpr);

    //Create ppc::Window
    Window kappaBlack(200, 200);
    //Add testEntity to ppc::Window
    kappaBlack.addEntity(testEntity);

	//Create ppc::Desktop
	char dummyTree = 't'; //using a dummy variable for Ctor until
	//the actual FileTree is completed
	Desktop myDesktop(dummyTree);
	myDesktop.addWindow(&kappaBlack);

////Start the game loop
    //Used to keep track time
	sf::Clock deltaTime;
    sf::Time framePeriod = sf::milliseconds(1000.0f / 30.f);
    while (window.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (deltaTime.getElapsedTime() > framePeriod) {
            // Clear screen
            window.clear(sf::Color::White);

            //Draw Objects
            window.draw(testRenderSpr);
            window.draw(S);
            
            //Update all Windows in the Desktop
            sf::Time dt = deltaTime.restart();
            myDesktop.update(dt);

            //Draw all the Windows in the Desktop
			myDesktop.refresh();
            window.draw(myDesktop);

            //Display final Window
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
