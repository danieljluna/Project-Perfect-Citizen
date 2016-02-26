#ifdef WINDOWS_MARKER
	#define resourcePath() string("Resources/")
#else
	#include "ResourcePath.hpp"
#endif

#include "createWindow.h"

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../Engine/Window.h"
#include "buttonRenderComponent.h"
#include "consoleUpdateComponent.h"
#include "../Engine/inputComponent.h"
#include "../Engine/InputHandler.h"
#include "../Engine/Entity.h"
#include "../Engine/subject.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/BorderDecorator.h"
#include "../Game/textOutputRenderComponent.h"


using namespace ppc;


void ppc::spawnConsole(WindowInterface*& windowToModify, 
	InputHandler & ih, NodeState & ns, 
	sf::Image& buttonSheet, float x, float y) {

	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS 
	///////////////////////////////////////
		/* Create the render components */
		sf::Image iconSheet;
		iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
		//sf::Image buttonSheet;
		//buttonSheet.loadFromFile(resourcePath() + "Windows_UI.png");
		buttonRenderComponent* textRenderComponent = 
			new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
		textRenderComponent->renderPosition(sf::Vector2f(0, 220));

		sf::Font myFont;
		myFont.loadFromFile(resourcePath() + "consola.ttf");
		int fontSize = 24;
		int windowOffset = 5;

		textInputRenderComponent* textInputBox = 
			new textInputRenderComponent(myFont, 0, 
				windowToModify->getSize().y - (fontSize+windowOffset),
				fontSize);
		textOutputRenderComponent* textDisplayBox = 
			new textOutputRenderComponent(myFont, ns, 0, 0, fontSize);

		/* Create the update component */
		consoleUpdateComponent* cup = new consoleUpdateComponent(ns);

		/* Create the input components */
		textInputKeys* tik = new textInputKeys(ih, 
			*textRenderComponent->getSprite(), *textInputBox, 
			*textDisplayBox, *cup);
	
	/////////////////////////////////////////
	/////// ENTITIES 
	///////////////////////////////////////
		Entity* textBox = new Entity();
		textBox->addComponent(textInputBox);
		textBox->addComponent(tik);
		textBox->addComponent(cup);

		Entity* textDisplay = new Entity();
		textDisplay->addComponent(textDisplayBox);

	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
		windowToModify->setPosition(x, y);
		windowToModify->addEntity(*textBox);
		windowToModify->addEntity(*textDisplay);
		windowToModify = new BorderDecorator(*windowToModify);
        dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
	
}

void ppc::spawnDatabase(WindowInterface*& windowToModify, InputHandler& ih, 
	sf::Image& buttonSheet, float x, float y) {
	/* Check to make sure the window passed isn't null */
	if (windowToModify == nullptr) { return; }

	/////////////////////////////////////////
	/////// COMPONENTS 
	///////////////////////////////////////
	/* Create the render components */
	sf::Image iconSheet;
	iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
	buttonRenderComponent* textRenderComponent =
		new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
	textRenderComponent->renderPosition(sf::Vector2f(0, 220));

	sf::Font myFont;
	myFont.loadFromFile(resourcePath() + "Consolas.ttf");
	int fontSize = 24;
	int windowOffset = 5;

	/////////////////////////////////////////
	/////// ENTITIES 
	///////////////////////////////////////


	/////////////////////////////////////////
	/////// WINDOW CONSTRUCTION
	///////////////////////////////////////
	windowToModify->setPosition(x, y);
	windowToModify = new BorderDecorator(*windowToModify);
    dynamic_cast<BorderDecorator*>(windowToModify)->addButton(buttonSheet, "localCloseButton");
}


