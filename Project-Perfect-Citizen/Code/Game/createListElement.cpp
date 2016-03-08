#include "createListElement.h"

void ppc::createEmailListElement(ppc::Entity& entityToModify, ppc::InputHandler& ih, sf::Font& f, std::string subjectLine, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	emailListElementRenderComponent* eLRC = new emailListElementRenderComponent(f, subjectLine, boxX, boxY, boxWidth, boxHeight, x, y, size);
	emailListElementInputComponent* eLIC = new emailListElementInputComponent(ih, eLRC->getListElementBoxBounds());
	entityToModify.addComponent(eLRC);
	entityToModify.addComponent(eLIC);
}