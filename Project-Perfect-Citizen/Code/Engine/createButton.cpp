#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createButton.h"

using namespace ppc;

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