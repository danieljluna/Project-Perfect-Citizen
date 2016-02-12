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
#include "Engine/mousePressButton.h"
#include "Engine/buttonRenderComponent.h"
#include "Engine/consoleIconRenderComponent.h"
#include "Engine/TreeCommands.h"
#include "Engine/NodeState.h"
#include "Engine/animatorComponent.hpp"
#include "Engine/textInputKeys.hpp"
#include "Engine/createWindow.h"

using namespace ppc;


//Note that this is placeholder for now
int main(int argc, char** argv) {

	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	//Example of using the debugger macro
	DEBUGF("ac", argc);

    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(1800, 1000), "SFML window");

	//Create the InputHandler
	ppc::InputHandler* inputHandle = new InputHandler();

	///////////////////////////TREE EXAMPLE//////////////////////
	std::cout << "START OF TREE EXAMPLE" << std::endl << std::endl;
	ppc::NodeState* testState = new NodeState();;
	testState->setUp(); /////SUPER IMPORTANT
	
	//////////////////////////MAKE/////////////////////////////////////
	std::vector<std::string> testMakeVector;
	testMakeVector.push_back("make");
	testMakeVector.push_back("testPlainFile");
	testMakeVector.push_back("This is what the plain File contains");
	
	commandFn makeFunction = findFunction(testMakeVector.at(0));
	makeFunction(*testState, testMakeVector);
	//////////////////////////MAKE/////////////////////////////////////
	//////////////////////////MKDIR////////////////////////////////////
	std::vector<std::string> testMkDirVector;
	testMkDirVector.push_back("mkdir");
	testMkDirVector.push_back("/testDirectory");

	commandFn mkDirFunction = findFunction(testMkDirVector.at(0));
	mkDirFunction(*testState, testMkDirVector);
	//////////////////////////MKDIR////////////////////////////////////
	//////////////////////////CD///////////////////////////////////////
	std::vector<std::string> testCdVector;
	testCdVector.push_back("cd");
	testCdVector.push_back("testDirectory");

	commandFn cdFunction = findFunction(testCdVector.at(0));
	cdFunction(*testState, testCdVector);
	//////////////////////////CD///////////////////////////////////////
	//////////////////////////LS///////////////////////////////////////
	std::vector<std::string> testLsVector;
	testLsVector.push_back("ls");
	testState->printWorking();

	commandFn lsFunction = findFunction(testLsVector.at(0));
	lsFunction(*testState, testLsVector);
	//////////////////////////LS///////////////////////////////////////
	std::cout << "END OF TREE EXAMPLE" << endl << endl;
	/////////////////////////END TREE EXAMPLE////////////////////

    
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
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");

	/////// Button Entity ////////
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spriteSheet, 0, 3, 1, 1);
	buttonRender->renderPosition(sf::Vector2f(10, 10));
	mousePressButton* mpb = new mousePressButton(*inputHandle,*buttonRender->getSprite());
	
    Entity* testEntity = new Entity();
	testEntity->addComponent(buttonRender);
    testEntity->addComponent(mpb);
	///////////////////////////////

	
	////// Icon Entity //////
	consoleIconRenderComponent* consoleIconRender = new consoleIconRenderComponent(iconSheet, 0, 0, 1);
	consoleIconRender->renderPosition(sf::Vector2f(120, 120));
    mousePressButton* mpb2 = new mousePressButton(*inputHandle, *consoleIconRender->getSprite());


	Entity* consoleIcon = new Entity();
	consoleIcon->addComponent(consoleIconRender);
	consoleIcon->addComponent(mpb2);
	/////////////////////////

	////// Icon Entity //////
	consoleIconRenderComponent* consoleIconRender3 = new consoleIconRenderComponent(iconSheet, 1, 0, 1);
	consoleIconRender3->renderPosition(sf::Vector2f(0, 120));
	mousePressButton* mpb3 = new mousePressButton(*inputHandle, *consoleIconRender3->getSprite());
    
	Entity* consoleIcon3 = new Entity();
	consoleIcon3->addComponent(consoleIconRender3);
	consoleIcon3->addComponent(mpb3);
	/////////////////////////
    
    /// Animated Icon Button Entity ///
    buttonRenderComponent* folderIconRender = new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
    folderIconRender->renderPosition(sf::Vector2f(0, 220));
    animatorComponent* animator = new animatorComponent(*folderIconRender, 0.05f);
    mousePressButton* mpb4 = new mousePressButton(*inputHandle, *folderIconRender->getSprite());
    
    Entity* folderIcon = new Entity();
    folderIcon->addComponent(folderIconRender);
    folderIcon->addComponent(animator);
    folderIcon->addComponent(mpb4);
    
  
    //Create ppc::Window
    Window* testWindow = new Window(600, 300,sf::Color(200,200,200));
	Window* consoleWindow = spawnConsole(*inputHandle, *testState);
	//testWindow->addInputComponent(mpb);
	//testWindow->addInputComponent(mpb2);
	testWindow->addEntity(*testEntity);
    testWindow->addEntity(*consoleIcon);
	testWindow->addEntity(*consoleIcon3);
    testWindow->addEntity(*folderIcon);
  
	//WindowLogger testWindowLogger(*testWindow,cout);
    //Add testEntity to ppc::Window
	//testWindowLogger.addEntity(testEntity);

	//Create ppc::Desktop
	Desktop myDesktop(*testState);

	//Add windows to Desktops
	//myDesktop.addWindow(&testWindowLogger);
	myDesktop.addWindow(testWindow);
	myDesktop.addWindow(consoleWindow);

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
			inputHandle->registerEvent(event);
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
