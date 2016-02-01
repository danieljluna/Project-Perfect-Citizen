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
    testRenderSpr.getSprite()->setScale(0.2, 0.2);
    testRenderSpr.getSprite()->setPosition(10, 10);

    //Create A TestRotateSprite
	testRotateSprite testSprCmpnt;
    
    //Put that Component into an Entity
    Entity testEntity;
    testEntity.addComponent(&testRenderSpr);

    //Create ppc::Window
    Window kappaBlack(100, 150);
    //Add testEntity to ppc::Window
    kappaBlack.addEntity(testEntity);

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
            window.draw(S);
            
            //Update kappaBlack
            kappaBlack.update(deltaTime.restart());

            //Draw kappaBlack ppc::Window
            kappaBlack.refresh();
            window.draw(kappaBlack);

            //Display final Window
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
