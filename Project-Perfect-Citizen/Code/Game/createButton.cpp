#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "../Engine/debug.h"
#include "createButton.h"

#include "../Engine/Network.h"
#include "../Engine/BaseFileType.h"
#include "../Engine/Window.h"
#include "../Engine/desktop.h"

#include "databaseSearchInputComponent.h"
#include "createWindow.h"
#include "ButtonBuilder.h"
#include "FloppyInputComponent.h"
#include "ConfirmWindowBuilder.h"
#include "../Engine/World.h"


using namespace ppc;

typedef bool (databaseSearchInputComponent::*backFn)(sf::Event&);

void ppc::spawnBackButton(databaseSearchInputComponent* db, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet,
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
	builder.setLabelSize(static_cast<int>(size));
	builder.setSpriteSheet(spritesheet);

	createWithEventFunc<databaseSearchInputComponent>(builder, entityToModify, db, &(ppc::goBackFn));
	
}


void ppc::spawnStartButton(ppc::Entity& entityToModify, Desktop& d, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {

	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(4, 0, 2, 1);
	builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
	builder.setLabelSize(static_cast<int>(size));
	builder.setSpriteSheet(spritesheet);
    

	createWithEventFunc<Desktop>(builder, entityToModify, &d, &(ppc::spawnStartMenu));

}

void ppc::spawnStartButton2(ppc::Entity& entityToModify, Desktop& d, FloppyInputComponent* flop, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(x, y));
    builder.setInputHandle(ih);
    builder.setSize(size);
    builder.setSpritesByIndicies(4, 0, 2, 1);
    builder.setLabelMessage("");
    sf::Font f;
    builder.setLabelFont(f);
    builder.setLabelSize(static_cast<int>(size));
    builder.setSpriteSheet(spritesheet);
    createWithEventFunc<FloppyInputComponent>(builder, entityToModify, flop, &(ppc::displayFloppy));
    
}

void ppc::spawnSuspicionButton(ppc::Entity& entityToModify, Desktop& d, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
	builder.setSpritesByIndicies(4, 0, 2, 1);
	builder.setLabelMessage("");
	sf::Font f;
	builder.setLabelFont(f);
	builder.setLabelSize(static_cast<int>(size));
	builder.setSpriteSheet(spritesheet);


	createWithEventFunc<Desktop>(builder, entityToModify, &d, &(ppc::spawnSuspicionMenu));

}

                                 
                                 

void ppc::spawnNetworkOkayButton(ppc::Network* nw, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size, NetworkCheckFunctor* ncf,
	sf::Font f) {
	
	ButtonBuilder builder;
	builder.setButtonPosition(sf::Vector2f(x, y));
	builder.setInputHandle(ih);
	builder.setSize(size);
    builder.setLabelFont(f);
	builder.setLabelSize(15);
	builder.setSpriteSheet(spritesheet);
	builder.setLabelMessage("SUBMIT");

	createWithEventFunc<NetworkCheckFunctor>(builder, entityToModify, ncf, &(ppc::runSubmitCheck));
	
}

void ppc::spawnConfirmedIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	
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

void ppc::spawnAlertIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	
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
void ppc::spawnPromptIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
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

void ppc::spawnDCPSIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
    /* Render Component */
    
    ButtonBuilder builder;
    builder.setButtonPosition(sf::Vector2f(x, y));
    builder.setInputHandle(ih);
    builder.setSize(size);
    builder.setSpritesByIndicies(6, 6, 1, 0);
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
		elementFunctions, 0.f, static_cast<float>(700-((elementNames.size()-1)*20)));
	ptr->addWindow(ContextMenu);
	return true;
}

bool ppc::spawnSuspicionMenu(Desktop * ptr, Event ev)
{
	ppc::WindowInterface* ContextMenu =
		new ppc::Window(200, 300, sf::Color(170, 170, 170));
	std::vector<std::string> elementNames;
	std::vector<bool(*)(Desktop*, Event ev)> elementFunctions;
	int a = File;
	ppc::BaseFileType testFile("file");
	testFile.setName("Testarino");
	elementNames.push_back(testFile.getName());
	//elementNames.push_back("Ayy Lmao 1");
	//elementNames.push_back("Ayy Lmao 2");
	elementFunctions.push_back(&(ppc::LogOff));
	//elementFunctions.push_back(&(ppc::displayFileInfo));
	//elementFunctions.push_back(&(ppc::LogOff));
	spawnContextMenu(*ptr, ContextMenu, ContextMenu->getInputHandler(), elementNames,
		elementFunctions, 300.f, static_cast<float>(700 - ((elementNames.size() - 1) * 20)));
	ptr->addWindow(ContextMenu);
	return true;
}



bool ppc::displayFloppy(FloppyInputComponent* ptr, Event ev) {
    ppc::Event ppcEv(ev);
    ppcEv.type = ppc::Event::FloppyType;
    ppcEv.floppy.sequence = 0;
    ppcEv.floppy.frame = 0;
    summonFloppyDialog(ptr, ppcEv);
    return true;
}

bool ppc::LogOff(Desktop* ptr, Event ev) {
	ppc::WindowInterface* ConfirmationWindow =
		new ppc::Window(600, 150, sf::Color(170, 170, 170));
	ConfirmWindowBuilder builder;

	builder.setButtonLabelFont(World::getFont(World::FontList::Consola));
	builder.setCancelButtonLabel("CANCEL");
	builder.setConfirmButtonLabel("LOG OUT");
	builder.setConfirmMessage("Are you sure you want to log off?\n(This will return you to the main menu)");
	builder.setMessageFont(World::getFont(World::FontList::Consola));
	builder.setMessageFontSize(16);
	builder.setPosition(sf::Vector2f(300,200));
	builder.setSpriteSheet(World::getCurrDesktop().getButtonSheet());
	builder.setWindowCaption("Log Off?");
	createWithEventFunc(builder, ConfirmationWindow, ptr, ppc::returnToLogin);
	ptr->addWindow(ConfirmationWindow);
	return true;
}

bool ppc::displayFileInfo(Desktop* desk, Event ev) {
	ppc::WindowInterface* infoWindow =
		new ppc::Window(600, 150, sf::Color(177, 177, 177));
	spawnErrorMessage(infoWindow, infoWindow->getInputHandler(), desk->getButtonSheet(), 300, 300, "HERES SOME FUKN INFO M8", "DELETE ME");
	desk->addWindow(infoWindow);
	return true;
}

bool ppc::returnToLogin(Desktop* desk, Event ev) {
	return true;
}
