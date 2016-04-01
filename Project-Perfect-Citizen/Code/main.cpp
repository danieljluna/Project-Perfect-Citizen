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
#include "Game/characterRender.hpp"
#include "Engine/debug.h"
#include "Engine/FreeFunctionObserver.h"
#include "Game/interpolateUpdateComponent.hpp"
#include "Engine/FreeFunctionObserver.h"

#include "Game/bootLoadingUpdateComponent.hpp"
#include "Game/bootLoadingAnimationRender.hpp"
#include "Game/endAnimationUpdateComponent.hpp"
#include "Game/endingAnimationRender.hpp"
#include "Game/Quitter.h"


using namespace ppc;



bool runBootDesktop(sf::RenderWindow& screen, ppc::Desktop& myDesktop) {
    
    Window* bootWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity loading;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    
    textLabelComponent* textLabel = new textLabelComponent(font,sf::Color::Green, 0,0, 20, " PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n   Beginning File System Initialization \n");
    
    bootLoadingAnimationRender* bootRender = new bootLoadingAnimationRender(*myDesktop.getButtonSheet(),*textLabel,7,5);

    
    bootLoadingUpdateComponent* bootUpdate = new bootLoadingUpdateComponent(*bootRender,0.1f);
    loading.addComponent(bootRender);
    loading.addComponent(bootUpdate);
    loading.addComponent(textLabel);
    bootWindow->addEntity(loading);
    
    myDesktop.addWindow(bootWindow);
    
    // Go into main game loop
    sf::Clock deltaTime;
    sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
    while (screen.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (screen.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::KeyPressed) {
                // Boots player to teacher desktop
                return false;
            }
            if (event.type == sf::Event::Closed) {
                screen.close();
            }
            
            //Input phase
            myDesktop.registerInput(event);
        }
        
        sf::Time elapsed = deltaTime.getElapsedTime();
        while (elapsed > framePeriod) {
            screen.clear(sf::Color::Black);
            sf::Time dt = deltaTime.restart();
            myDesktop.update(dt);
            elapsed -= framePeriod;
        }
        myDesktop.refresh();
        screen.draw(myDesktop);
        screen.display();
    }
    return false;
    
}

//struct A {
	//bool b;
//};

//bool(*triggerEnd)(BaseFileType& obj, sf::Event& ev);



bool runEndDesktop(sf::RenderWindow& screen, ppc::Desktop& myDesktop) {

    Window* endWindow = new Window(1800,1000,sf::Color(30,32,33));
    
    Entity ending;
    
    sf::Font font;
    font.loadFromFile(resourcePath() + "consola.ttf");
    
    endingAnimationRender* endRender = new endingAnimationRender(*myDesktop.getButtonSheet());
    endAnimationUpdateComponent* endUpdate = new endAnimationUpdateComponent(*endRender, 0.1f);
    
    
    
    ending.addComponent(endRender);
    ending.addComponent(endUpdate);
    endWindow->addEntity(ending);
    
    myDesktop.addWindow(endWindow);
    
    // Go into main game loop
    sf::Clock deltaTime;
    sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
    while (screen.isOpen()) {
        //Process sf::events
        sf::Event event;
        while (screen.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::KeyPressed) {
                // Boots player to teacher desktop
                return false;
            }
            if (event.type == sf::Event::Closed) {
                screen.close();
            }
            
            //Input phase
            myDesktop.registerInput(event);
        }
        
        sf::Time elapsed = deltaTime.getElapsedTime();
        while (elapsed > framePeriod) {
            screen.clear(sf::Color::Black);
            sf::Time dt = deltaTime.restart();
            myDesktop.update(dt);
            elapsed -= framePeriod;
        }
        myDesktop.refresh();
        screen.draw(myDesktop);
        screen.display();
    }
    return false;
    
}


bool runPlayerDesktop(sf::RenderWindow& screen, ppc::Desktop& myDesktop) {

	createPlayerDesktop(myDesktop, *myDesktop.getDesktopWindow(), 
		myDesktop.getInputHandler(), *myDesktop.getIconSheet(), *myDesktop.getButtonSheet());

	//FreeFunctionObserver <A>(&BaseFileType, triggerEnd);
	//myDesktop.getNodeState().getDirString()
	// Go into main game loop
	sf::Clock deltaTime; 
	sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
	while (screen.isOpen()) {
        if (quitter) {
            return false;
        }
		//Process sf::events
		//cout << "from main: " << myDesktop.getNodeState().getDirString() << endl;
		sf::Event event;
		while (screen.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                screen.close();
            } else if (event.type == sf::Event::KeyPressed) {
                //Close
                if ((event.key.code == sf::Keyboard::Period) && (event.key.control)) {
                    return false;
                }
            }

			//Input phase
			myDesktop.registerInput(event);
		}

		sf::Time elapsed = deltaTime.getElapsedTime();
		while (elapsed > framePeriod) {
			screen.clear(sf::Color::Black);
			sf::Time dt = deltaTime.restart();
			myDesktop.update(dt);
			elapsed -= framePeriod;
		}
		myDesktop.refresh();
		screen.draw(myDesktop);
		screen.display();
	}
	return false;

}


bool runTargetDesktop(sf::RenderWindow& screen, ppc::Desktop& myDesktop) {

	createTeacherDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), *myDesktop.getIconSheet(), *myDesktop.getButtonSheet());

		// Go into main game loop
		sf::Clock deltaTime; 
		sf::Time framePeriod = sf::milliseconds(sf::Int32(1000.0f / 30.f));
		while (screen.isOpen()) {
            if (quitter) {
                return false;
            }
			//Process sf::events
			sf::Event event;
            while (screen.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    screen.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    //Close
                    if ((event.key.code == sf::Keyboard::Period) && (event.key.alt)) {
                        return false;
                    }
                }

                //Input phase
                myDesktop.registerInput(event);
            }

			sf::Time elapsed = deltaTime.getElapsedTime();
			while (elapsed > framePeriod) {
				screen.clear(sf::Color::Black);
				sf::Time dt = deltaTime.restart();
				myDesktop.update(dt);
				elapsed -= framePeriod;
			}
			myDesktop.refresh();
			screen.draw(myDesktop);
			screen.display();
		}
		return false;
}

int main(int argc, char** argv) {

    DBG_INIT();
	//Scans Debug Flags
	Debug::scanOpts(argc, argv);
	DEBUGF("ac", argc);


	bool BootToTitleCard = false; 
    // Create the main sf::window
    sf::RenderWindow screen(sf::VideoMode(1000, 800), "SFML window");

	//bool coolReturnValue = (*cool.*(c->functionPointer))(sf::Event());

	///////////// Load Spritesheets/Textures/Background Images ////////
	sf::Sprite playerWallpaper;
	sf::Sprite teacherWallpaper;
	sf::Texture playerWallpaperTexture;
	sf::Texture teacherWallpaperTexture;
	playerWallpaperTexture.loadFromFile(resourcePath() + "Wallpaper.png");
	teacherWallpaperTexture.loadFromFile(resourcePath() + "Teacher_Wallpaper.png");

	playerWallpaper.setTexture(playerWallpaperTexture);
	teacherWallpaper.setTexture(teacherWallpaperTexture);

	playerWallpaper.setScale(0.7f, 0.7f);
	playerWallpaper.setPosition(0, 0);

    sf::Image buttonSheet;
	buttonSheet.loadFromFile(resourcePath() + "Windows_UI.png");
    sf::Image pixelSheet;
    pixelSheet.loadFromFile(resourcePath() + "Pixel_Title.png");
    sf::Image iconSheet;
    iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
	sf::Image teacherIconSheet;
	teacherIconSheet.loadFromFile(resourcePath() + "Teacher_Icon_Sheet.png");
	///////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////
	//Assuming Builders Should Eventually Go Here
	/////////////////////////////////////////////
	//Placeholder stuff for now.

	//runBootDesktop
	ppc::NodeState bootState;
	Window* bootWindow = new Window(1800, 1000, sf::Color(0, 0, 0));
	Desktop bootDesktop(*bootWindow, bootState);
	bootDesktop.setIconSheet(iconSheet);
	bootDesktop.setButtonSheet(buttonSheet);
	bootDesktop.addBackgroundCmpnt(bootWindow, playerWallpaper);

	//runPlayerDesktop
	ppc::NodeState playerState;
	playerState.setUp();
	Window* playerDesktopWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Desktop playerDesktop(*playerDesktopWindow, playerState);
	playerDesktop.setIconSheet(iconSheet);
	playerDesktop.setButtonSheet(buttonSheet);
	playerDesktop.addBackgroundCmpnt(playerDesktopWindow, playerWallpaper);

	//runTargetDesktop
	ppc::NodeState targetState;
	targetState.setUp();
	Window* targetDesktopWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Desktop targetDesktop(*targetDesktopWindow, targetState);
	targetDesktop.setIconSheet(iconSheet);
	targetDesktop.setButtonSheet(buttonSheet);
	targetDesktop.addBackgroundCmpnt(targetDesktopWindow, teacherWallpaper);

	//runEndDesktop
	ppc::NodeState endState;
	Window* endWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Desktop endDesktop(*endWindow, endState);
	endDesktop.setIconSheet(iconSheet);
	endDesktop.setButtonSheet(pixelSheet);
	endDesktop.addBackgroundCmpnt(endWindow, playerWallpaper);


	/////////////////////////////////////////////
	//Assuming Builders End Here
	/////////////////////////////////////////////
	
	//Main Loops for each Desktops
    while (runBootDesktop(*&screen, *&bootDesktop)) {}
    quitter = false;
	while (runPlayerDesktop(*&screen, *&playerDesktop)) {}
    quitter = false;
	while (runTargetDesktop(*&screen, *&targetDesktop)) {}
    while (runEndDesktop(*&screen, *&endDesktop)) {}

    return EXIT_SUCCESS;
}



