//Used to get XCODE working/////////////////////////////////

#ifdef WINDOWS_MARKER
    #define resourcePath() string("Resources/")
#else
    #include "ResourcePath.hpp"
#endif

///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Library/json/json.h"

#include "Engine/testRenderSprite.h"
#include "Engine/InputHandler.h"
#include "Engine/subject.h"
#include "Engine/TestObserver.h"
#include "Engine/debug.h"
#include "Engine/entity.h"
#include "Engine/Window.h"
#include "Engine/desktop.h"
#include "Engine/DesktopLogger.h"
#include "Engine/WindowLogger.h"
#include "Engine/mousePressButton.h"
#include "Engine/buttonRenderComponent.h"
#include "Engine/consoleIconRenderComponent.h"
#include "Engine/TreeCommands.h"
#include "Engine/NodeState.h"


using namespace ppc;


//Note that this is placeholder for now
int main(int argc, char** argv) {
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	//Example of using the debugger macro
	DEBUGF("ac", argc);

    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(800, 600), "SFML window");

	//Create the InputHandler
	ppc::InputHandler inputHandle;

    //Define a Sprite
    sf::Sprite S;
    sf::Texture T;
    if (!(T.loadFromFile(resourcePath() + "Wallpaper.png"))) {
        //Test for failure
        cerr << "COULD NOT LOAD\n";
        std::system("PAUSE");
        return -1;
    };
    S.setTexture(T);
    S.setPosition(0, 0);
    S.setScale(0.7f, 0.7f);
    

    sf::Image spriteSheet;
    spriteSheet.loadFromFile(resourcePath() + "Windows_UI.png");

	sf::Image iconSheet;
	iconSheet.loadFromFile(resourcePath() + "Windows_Icons.png");

	/////// Button Entity ////////
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spriteSheet, 0, 3, 1);
	buttonRender->renderPosition(sf::Vector2f(10, 10));
	mousePressButton* mpb = new mousePressButton(inputHandle,*buttonRender->getSprite());
	
    Entity* testEntity = new Entity();
	testEntity->addComponent(buttonRender);
    testEntity->addComponent(mpb);
	///////////////////////////////

	
	////// Icon Entity //////
	consoleIconRenderComponent* consoleIconRender = new consoleIconRenderComponent(iconSheet, 0, 0, 1);
	consoleIconRender->renderPosition(sf::Vector2f(120, 120));
    mousePressButton* mpb2 = new mousePressButton(inputHandle, *consoleIconRender->getSprite());

	Entity* consoleIcon = new Entity();
	consoleIcon->addComponent(consoleIconRender);
	consoleIcon->addComponent(mpb2);
	/////////////////////////


    //Create ppc::Window
    Window* testWindow = new Window(200, 200,sf::Color(200,200,200));
	testWindow->addEntity(*testEntity);
    testWindow->addEntity(*consoleIcon);
	//WindowLogger testWindowLogger(*testWindow,cout);
    //Add testEntity to ppc::Window
	//testWindowLogger.addEntity(testEntity);

	//Create ppc::Desktop
	char dummyTree = 't'; //using a dummy variable for Ctor until
	//the actual FileTree is completed
	Desktop myDesktop(dummyTree);

	//Add windows to Desktops
	//myDesktop.addWindow(&testWindowLogger);
	myDesktop.addWindow(testWindow);

    ///////////////////////////////////////////////////////////////////
	// Start the game loop
	///////////////////////////////////////////////////////////////////
	sf::Clock deltaTime; //define deltaTime
    //Used to keep track time
    sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
    while (screen.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (screen.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
				screen.close();

			//Input phase
			inputHandle.registerEvent(event);
        }

        if (deltaTime.getElapsedTime() > framePeriod) {

            // Clear screen
			screen.clear(sf::Color::White);

            //Draw Background
			screen.draw(S);
            
            //Update all Windows in the Desktop
            sf::Time dt = deltaTime.restart();
			myDesktop.update(dt);

            //Draw all the Windows in the Desktop
			myDesktop.refresh();

			//Logger should not be used in place of passing
			//the actual drawn Desktop
			screen.draw(myDesktop);

            //Display final Window
			screen.display();
        }
    }
	
    return EXIT_SUCCESS;
}
