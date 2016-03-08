#include "createListElement.h"

void ppc::createEmailListElement(ppc::Entity& entityToModify, sf::Font& f, std::string subjectLine, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	emailListElementRenderComponent* eLRC = new emailListElementRenderComponent(f, subjectLine, boxX, boxY, boxWidth, boxHeight, x, y, size);
	entityToModify.addComponent(eLRC);

}