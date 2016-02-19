#ifdef WINDOWS_MARKER
#define resourcePath() string("Resources/")
#else
#include "ResourcePath.hpp"
#endif

#include "createIcon.h"
using namespace ppc;

void spawnFolderIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {

	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 0, 1, 4);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);
	mousePressButton* mpbFolder = new mousePressButton(ih, *IconRender->getSprite(), "folderIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbFolder);
}

void spawnSettingsIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {

	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 1, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "settingsIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);

}

void spawnChatIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 2, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "chatIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnSearchIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 3, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "searchIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnDataGraphIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 4, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "dataGraphIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnHelpIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 5, 1, 2);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "helpIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnBrowserIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 6, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "browserIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnHardDriveIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, ppc::InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {
	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 7, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Component ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "hardDriveIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);

	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(iconInputComp);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
}

void spawnConsoleIcon(ppc::Entity& entityToModify, ppc::Desktop& dT, InputHandler& ih, sf::Image& iconSheet, float x, float y, float size, float animSpeed) {

	/// Render Component ///
	buttonRenderComponent* IconRender = new buttonRenderComponent(iconSheet, 0, 8, 1, 1);
	IconRender->setImageScale(size, size);
	IconRender->renderPosition(sf::Vector2f(x, y));

	// Animator (Update) Component ///
	animatorComponent* animator = new animatorComponent(*IconRender, animSpeed);

	/// Input Components ///
	mousePressButton* mpbIcon = new mousePressButton(ih, *IconRender->getSprite(), "consoleIcon");
	iconInputComponent* iconInputComp = new iconInputComponent(dT);
	entityToModify.addComponent(IconRender);
	entityToModify.addComponent(animator);
	entityToModify.addComponent(mpbIcon);
	entityToModify.addComponent(iconInputComp);


}



