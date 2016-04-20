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
	
	/* Render Component */
    buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 0, 2, 1);
    buttonRender->setImageScale(size, size);
    buttonRender->renderPosition(sf::Vector2f(x, y));

    /* Input Component*/
    mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "backButton");

    setOnPress(mpb, db, &(ppc::goBackFn));

    entityToModify.addComponent(buttonRender);
    entityToModify.addComponent(mpb);
}


void spawnStartButton(ppc::Entity& entityToModify, Desktop& d, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 0, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "startButton");

	setOnPress(mpb, &d, &(ppc::spawnStartMenu));

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);

	buttonRender->renderPosition(sf::Vector2f(x, y));
}

void spawnNextButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 1, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "nextButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnBlankLargeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 1, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "blankLargeButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

// * THIS IS TEMPORARY FOR FIRST PLAYABLE *//
void spawnNetworkOkayButton(ppc::Network* nw, ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size, NetworkCheckFunctor* ncf) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 2, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "okayButton");

	setOnPress(mpb, ncf, &(ppc::runSubmitCheck));

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnOkayButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 2, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "okayButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnCancelButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 2, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "cancelButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnCloseButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet, float x, float y, float size) {

	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spriteSheet, 0, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));
	
	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "closeButton");
	
	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnMaximizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "maximizeButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnMinimizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "minimizeButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnBlankSmallButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "blankSmallButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnUpButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "upButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnDownButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "downButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnRightButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "rightButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnLeftButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "leftButton");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnScrollBarContainer(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 5, 3, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "scrollBarContainer");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnScrollBarHandle(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 5, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, buttonRender->getSprite()->getGlobalBounds(), "scrollBarHandle");

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnConfirmedIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 5, 1, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	entityToModify.addComponent(buttonRender);
}

void spawnAlertIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 5, 5, 1, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	entityToModify.addComponent(buttonRender);
}
void spawnPromptIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
    /* Render Component */
    buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 7, 6, 1, 0);
    buttonRender->setImageScale(size, size);
    buttonRender->renderPosition(sf::Vector2f(x, y));
    
    entityToModify.addComponent(buttonRender);
}


bool ppc::spawnStartMenu(Desktop* ptr, Event ev) {
	ppc::WindowInterface* ContextMenu =
		new ppc::Window(200, 300, sf::Color(170, 170, 170));
	std::vector<std::string> elementNames;
	std::vector<bool(*)(Desktop*, Event ev)> elementFunctions;
	elementNames.push_back("Log Off");
	elementNames.push_back("Log off 2");
	elementFunctions.push_back(&(ppc::LogOff));
	elementFunctions.push_back(&(ppc::LogOff));
	
	spawnContextMenu(*ptr, ContextMenu, ContextMenu->getInputHandler(), elementNames,
		elementFunctions, 0, 700-((elementNames.size()-1)*20));
	ptr->addWindow(ContextMenu);
	return true;
}
bool ppc::LogOff(Desktop* ptr, Event ev) {
	cout << "Log Off" << endl;
	return true;
}





