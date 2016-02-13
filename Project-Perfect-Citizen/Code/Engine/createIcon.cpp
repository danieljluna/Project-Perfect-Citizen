#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createIcon.h"

using namespace ppc;

void spawnConsoleIcon(ppc::Entity& entityToModify, InputHandler& ih, sf::Image& iconSheet, float x, float y, float size) {

	/// Render Component ///
	buttonRenderComponent* consoleIconRender = new buttonRenderComponent(iconSheet, 0, 8, 1, 2);
	consoleIconRender->setImageScale(size, size);
	consoleIconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*consoleIconRender, 0.05f);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *consoleIconRender->getSprite());

	entityToModify.addComponent(consoleIconRender);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);

}

void spawnSettingsIcon(ppc::Entity& entityToModify,  InputHandler& ih, sf::Image& iconSheet, float x, float y, float size) {

	/// Render Component ///
	buttonRenderComponent* settingsIconRender = new buttonRenderComponent(iconSheet, 0, 1, 1, 3);
	settingsIconRender->setImageScale(size, size);
	settingsIconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*settingsIconRender, 0.05f);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *settingsIconRender->getSprite());

	entityToModify.addComponent(settingsIconRender);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);

}

void spawnFolderIcon(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size) {
	
	buttonRenderComponent* folderIconRender = new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
	folderIconRender->setImageScale(size, size);
	folderIconRender->renderPosition(sf::Vector2f(x, y));
	animatorComponent* animator = new animatorComponent(*folderIconRender, 0.05f);
	mousePressButton* mpbFolder = new mousePressButton(ih, *folderIconRender->getSprite());

	entityToModify.addComponent(folderIconRender);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbFolder);
}