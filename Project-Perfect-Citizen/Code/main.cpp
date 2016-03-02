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
#include "Game/testRenderSprite.h"
#include "Engine/InputHandler.h"
#include "Engine/subject.h"
#include "Engine/debug.h"
#include "Engine/entity.h"
#include "Engine/Window.h"
#include "Engine/desktop.h"
#include "Game/mousePressButton.h"
#include "Game/buttonRenderComponent.h"
#include "Game/consoleIconRenderComponent.h"
#include "Game/TreeCommands.h"
#include "Engine/NodeState.h"
#include "Game/animatorComponent.hpp"
#include "Game/textInputKeys.hpp"
#include "Game/createWindow.h"
#include "Game/createIcon.h"
#include "Game/createButton.h"
#include "Engine/BorderDecorator.h"
#include "Game/createDesktop.h"
#include "Game/desktopExtractionComponent.hpp"
#include "Game/expressionistParser.hpp"
#include "Engine/Audio/Audio.h"
#include "Engine/Audio/Sounds.h"
#include "Engine/Audio/DesktopAudio.h"
#include "Engine/Audio/AudioLocator.h"
#include "Engine/Audio/AudioLogger.h"
#include "Engine/Audio/AudioLocator.h"
#include "Engine/Audio/NullAudio.h"
#include "Game/PipelineCharacter.h"
#include "Game/Database.h"
#include "Engine/Audio/AudioQueue.h"
#include "Engine/Network.h"
#include "Game/BootLoader.hpp"

//#include "Game/BootLoader.hpp"
#include "Engine/FunctionObserver.h"
#include "Game/characterRender.hpp"



using namespace ppc;

using testFunc = bool(*)(sf::Event&);

bool printFunc(sf::Event& ev) {
	std::cout << "inside printFunc" << std::endl;
	return true;
}

//Note that this is placeholder for now
int main(int argc, char** argv) {

    DBG_INIT();

	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	DEBUGF("ac", argc);

    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(1000, 800), "SFML window");

	//////////////////////////SOUND STUFF//////////////////////////////
	//AudioLocator::initialize();
	//ppc::NullAudio dAudio;
	//AudioLocator::assign(&dAudio);
	//AudioLogger logger(dAudio);
	//AudioLocator::assign(&logger);
	//Audio* audio = AudioLocator::getAudio();
	//audio->playSound(ppc::Sounds::gunshot);

	//AudioQueue aq(5);
	//int gunshots = aq.addSound("shots", "gunshots.wav");
	//aq.playSound(gunshots);
	//aq.popAndPlay();
	///////////////////////////////////////////////////////////////////

    ////////////////// BACKGROUND IMAGE ////////////////////
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
	///////////////////////////////////////////////////////

	///////////// Load Spritesheets/Textures //////////////
    sf::Image spriteSheet;
	spriteSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
    sf::Image faceSheet;
    faceSheet.loadFromFile(resourcePath() + "Face_Sheet.png");

    
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	///// CREATE THE PLAYER DESKTOP
	/////////////////////////////////////////////////////////
	ppc::NodeState testState;
	testState.setUp();
	Window* desktopWindow = new Window(1800,1000,sf::Color(0,0,0));
    
    Desktop myDesktop(*desktopWindow, testState);
    myDesktop.addBackgroundCmpnt(desktopWindow, S);
    createPlayerDesktop(myDesktop, *desktopWindow, myDesktop.getInputHandler(), iconSheet, spriteSheet);
    
    //Entity* aCharacter = new Entity();
    //characterRender* characterRend = new characterRender(faceSheet);
    //aCharacter->addComponent(characterRend);
    
   // desktopWindow->addEntity(*aCharacter);
    
    
    
    
    //////////////////////////////////////////////////////////
    ///// TEMPORARY BOOT LOADING SCREEN SETUP
    /////////////////////////////////////////////////////////
   /* bool hasBooted = true;
    int step = 0;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    sf::Text text;
    text.setPosition(0, 0);
    text.setColor(sf::Color::Green);
    text.setCharacterSize(18);
    text.setFont(font);

    std::string renderString = "";
    text.setString(renderString);*/
    
	

	///////////////////////////////////////////////////////
	///// Testing Vertex Drawing //////////////////////////
	///////////////////////////////////////////////////////

	Network net(3);

	PipelineCharacter Bob;
	PipelineCharacter Tim;
	PipelineCharacter Rob;
	Bob.generate();
	Tim.generate();
	Rob.generate();

	net.vert(0).setCharacter(Bob);
	net.vert(1).setCharacter(Tim);
	net.vert(2).setCharacter(Rob);
	net.vert(0).setPosition(360,300);
	net.vert(1).setPosition(500,600);
	net.vert(2).setPosition(100,200);
	DraggableInput di(net.vert(0));
	net.vert(0).applyDraggable(di, desktopWindow->getInputHandler());
	di.setBounds(net.vert(0).getGlobalBounds());
	Edge e1, e2;
	e1.setColorRed();
	e2.setColorGreen();
	e1.setWeight(1);
	e1.setRelation("");

	net.setEdge(0, 1, e1);
	net.setEdge(1, 2, e2);
	




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
			//if(hasBooted)
                myDesktop.registerInput(event);
        }

        sf::Time elapsed = deltaTime.getElapsedTime();
        while (elapsed > framePeriod) {

            // Clear screen
            screen.clear(sf::Color::Black);

            //Update all Windows in the Desktop
            sf::Time dt = deltaTime.restart();
            //if(hasBooted)
                myDesktop.update(dt);

            elapsed -= framePeriod;
        }
        //////////////////////////////////////////////////////////
        ///// I KNOW THIS IS A REALLY GROSS LOOP
        ///// TEMPORARY BOOT LOADING SCREEN
        /////////////////////////////////////////////////////////
        /*if (!hasBooted) {
            renderString = bootLoad(step, renderString);
            if (step == 6300)
                hasBooted = true;
            step++;
            text.setString(renderString);
            screen.draw(text);*/
        //} else {
           //myDesktop.refresh();
           //screen.draw(myDesktop);
       // }

            //Draw all the Windows in the Desktop
			myDesktop.refresh();

			//Logger should not be used in place of passing
			//the actual drawn Desktop
			screen.draw(myDesktop);
			screen.draw(net);

            //Display the final window
			screen.display();
    }

    return EXIT_SUCCESS;
}



