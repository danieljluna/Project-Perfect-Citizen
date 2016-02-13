#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createButton.h"

using namespace ppc;

void spawnBackButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 0, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnStartButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 0, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnNextButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 1, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnBlankLargeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 1, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnOkayButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 2, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnCancelButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 2, 2, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnCloseButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spriteSheet, float x, float y, float size) {

	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spriteSheet, 0, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));
	
	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());
	
	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnMaximizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnMinimizeButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnBlankSmallButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 3, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnUpButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnDownButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnRightButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 4, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnLeftButton(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 4, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnScrollBarContainer(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 2, 5, 3, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnScrollBarHandle(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 0, 5, 1, 1);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnConfirmedIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 6, 5, 1, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}

void spawnAlertIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& spritesheet, float x, float y, float size) {
	/* Render Component */
	buttonRenderComponent* buttonRender = new buttonRenderComponent(spritesheet, 5, 5, 1, 0);
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(x, y));

	/* Input Component*/
	mousePressButton* mpb = new mousePressButton(ih, *buttonRender->getSprite());

	entityToModify.addComponent(buttonRender);
	entityToModify.addComponent(mpb);
}
