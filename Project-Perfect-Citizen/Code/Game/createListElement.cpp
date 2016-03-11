#include "createListElement.h"

void ppc::createEmailListElement(ppc::Entity& entityToModify, Desktop& dT, sf::Image& bS, ppc::InputHandler& ih, sf::Font& f,
	Email eM, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	emailListElementRenderComponent* eLRC = new emailListElementRenderComponent(f, eM, boxX, boxY, boxWidth, boxHeight, x, y, size);
	emailListElementInputComponent* eLIC = new emailListElementInputComponent(dT, ih, eM, bS, eLRC->getListElementBoxBounds());
	entityToModify.addComponent(eLRC);
	entityToModify.addComponent(eLIC);
}