#include "createListElement.h"
#include "buttonRenderComponent.h"

void ppc::createEmailListElement(ppc::Entity& entityToModify, Desktop& dT, sf::Image& bS, ppc::InputHandler& ih, sf::Font& f,
	Email eM, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	emailListElementRenderComponent* eLRC = new emailListElementRenderComponent(f, eM, boxX, boxY, boxWidth, boxHeight, x, y, size);
	emailListElementInputComponent* eLIC = new emailListElementInputComponent(dT, ih, eM, bS, eLRC->getListElementBoxBounds());

	
	buttonRenderComponent* emailIcon = new buttonRenderComponent(*dT.getIconSheet(), 0, 10, 1, 2);
	emailIcon->setImageScale(size, size);
	emailIcon->renderPosition(sf::Vector2f(x+ 10, y-10));
	emailIcon->setButtonType("ICON");
	if (eM.getReadFlag()) emailIcon->setSprite(1, 10, 1);

	entityToModify.addComponent(eLRC);
	entityToModify.addComponent(eLIC);
	entityToModify.addComponent(emailIcon);
}