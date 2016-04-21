#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "../Engine/debug.h"
#include "createButton.h"
#include "databaseSearchInputComponent.h"
#include "../Engine/Network.h"
#include "NetworkCheckFunctor.h"
#include "createWindow.h"
#include "ButtonBuilder.h"

using namespace ppc;

typedef bool (databaseSearchInputComponent::*backFn)(sf::Event&);

void spawnBackButton(databaseSearchInputComponent* db, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet,
    float x, float y, float size)
{

	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(0, 0, 2, 1);
	builder.setLabelMessage("");
    sf::Font f;
	builder.setLabelFont(f);
	builder.setLabelSize(size);
	builder.setSpriteSheet(spritesheet);

	createWithEventFunc<databaseSearchInputComponent>(builder, entityToModify, db, &(ppc::goBackFn));
	
}


void spawnStartButton(ppc::Entity& entityToModify, Desktop& d, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {

	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(4, 0, 2, 1);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(size);
	builder.setSpriteSheet(spritesheet);
    

	createWithEventFunc<Desktop>(builder, entityToModify, &d, &(ppc::spawnStartMenu));

}

void spawnStartButton2(ppc::Entity& entityToModify, Desktop& d, FloppyInputComponent* flop, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(x, y));
    builder.setInputHandle(ih);
    builder.setSize(size);
    builder.setSpritesByIndicies(4, 0, 2, 1);
    builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
    builder.setLabelSize(size);
    builder.setSpriteSheet(spritesheet);
    

    createWithEventFunc<FloppyInputComponent>(builder, entityToModify, flop, &(ppc::displayFloppy));
    
}

                                 
                                 

void spawnNetworkOkayButton(ppc::Network* nw, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size, NetworkCheckFunctor* ncf) {
	
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(0, 2, 2, 1);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(20);
	builder.setSpriteSheet(spritesheet);

	createWithEventFunc<NetworkCheckFunctor>(builder, entityToModify, ncf, &(ppc::runSubmitCheck));
	
}

void spawnConfirmedIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(6, 5, 1, 0);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(20);
	builder.setSpriteSheet(spritesheet);
	builder.setNonClickable();
	builder.create(entityToModify);

}

void spawnAlertIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(5, 5, 1, 0);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(20);
	builder.setSpriteSheet(spritesheet);
	builder.setNonClickable();
	builder.create(entityToModify);

}
void spawnPromptIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
    /* Render Component */

	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(7, 6, 1, 0);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(20);
	builder.setSpriteSheet(spritesheet);
	builder.setNonClickable();
	builder.create(entityToModify);

}


bool ppc::spawnStartMenu(Desktop* ptr, Event ev) {
	ppc::WindowInterface* ContextMenu =
		new ppc::Window(200, 300, sf::Color(170, 170, 170));
	std::vector<std::string> elementNames;
	std::vector<bool(*)(Desktop*, Event ev)> elementFunctions;
	elementNames.push_back("Log Off");
	elementFunctions.push_back(&(ppc::LogOff));
	
	spawnContextMenu(*ptr, ContextMenu, ContextMenu->getInputHandler(), elementNames,
		elementFunctions, 0, 700-((elementNames.size()-1)*20));
	ptr->addWindow(ContextMenu);
	return true;
}

bool ppc::displayFloppy(FloppyInputComponent* ptr, Event ev) {
    ppc::Event ppcEv(ev);
    ppcEv.type = ppc::Event::FloppyType;
    ppcEv.floppy.sequence = 0;
    ppcEv.floppy.frame = 1;
    summonFloppyDialog(ptr, ppcEv);
    return true;
}

bool ppc::LogOff(Desktop* ptr, Event ev) {
	cout << "Implement Log Off" << endl;
	return true;
}





