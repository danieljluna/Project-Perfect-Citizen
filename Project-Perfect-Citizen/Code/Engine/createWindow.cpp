
#ifdef WINDOWS_MARKER
	#define resourcePath() string("Resources/")
#else
	#include "ResourcePath.hpp"
#endif

#include "createWindow.h"

using namespace ppc;

ppc::Window* spawnConsole(InputHandler& ih, NodeState& ns) {

	
	/////// COMPONENTS /////////
		/* Create the render component */
		sf::Image iconSheet;
		iconSheet.loadFromFile(resourcePath() + "Icon_Sheet.png");
		buttonRenderComponent* textRenderComponent = new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
		textRenderComponent->renderPosition(sf::Vector2f(0, 220));

		/* Create the update component */
		consoleUpdateComponent* cup = new consoleUpdateComponent(ns);

		/* Create the input component */
		sf::Font myFont;
		myFont.loadFromFile(resourcePath() + "Consolas.ttf");
		textInputRenderComponent* textInputBox = new textInputRenderComponent(myFont);
		textInputKeys* tik = new textInputKeys(ih, *textRenderComponent->getSprite(), *textInputBox, *cup);



	///////////////////////////////////////


	///// ENTITIES ////////
		Entity* textBox = new Entity();
		textBox->addComponent(textInputBox);
		textBox->addComponent(tik);
		textBox->addComponent(cup);
	//////////////////////////////////


	/////// WINDOW  /////////
		Window* consoleWindow = new Window(600, 300, sf::Color(51, 50, 161));
		consoleWindow->setPosition(0, 300);
		consoleWindow->addEntity(*textBox);
		return consoleWindow;
	////////////////////////
	
	
}