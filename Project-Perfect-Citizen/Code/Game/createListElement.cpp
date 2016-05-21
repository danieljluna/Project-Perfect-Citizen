#include "createListElement.h"

#include "../Engine/desktop.h"

#include "contextListElementRenderComponent.h"
#include "buttonRenderComponent.h"
#include "TextDisplayBuilder.h"
#include "TextDisplayRenderComponent.h"
#include "mousePressButton.h"
#include "emailListElementRenderComponent.h"
#include "emailListElementInputComponent.h"
#include "Email.h"


using namespace ppc;

void ppc::createEmailListElement(ppc::Entity& entityToModify, Desktop& dT, sf::Image& bS, ppc::InputHandler& ih, sf::Font& f,
	Email* eM, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	emailListElementRenderComponent* eLRC = new emailListElementRenderComponent(f, eM, boxX, boxY, boxWidth, boxHeight, x, y, size);
	emailListElementInputComponent* eLIC = new emailListElementInputComponent(dT, ih, eM, bS, eLRC->getListElementBoxBounds());

	buttonRenderComponent* emailIcon = new buttonRenderComponent(dT.getIconSheet(), 0, 10, 1, 2);
	emailIcon->setImageScale(static_cast<float>(size), static_cast<float>(size));
	emailIcon->renderPosition(sf::Vector2f(static_cast<float>(x+ 10), static_cast<float>(y-10)));
	emailIcon->setButtonType("ICON");
	if (eM->getReadFlag()) emailIcon->setSprite(1, 10, 1);

	entityToModify.addComponent(eLRC);
	entityToModify.addComponent(eLIC);
	entityToModify.addComponent(emailIcon);
}

void ppc::createContextListElement(ppc::Entity& entityToModify, WindowInterface* win, Desktop& dt, ppc::InputHandler& ih,
	sf::Font& f, std::string s, bool(*func)(Desktop* desk, Event ev), int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {

	contextListElementRenderComponent* rc = new contextListElementRenderComponent(win, f,
		s, boxX, boxY, boxWidth, boxHeight, x, y, size);

	TextDisplayRenderComponent *rc2 = new TextDisplayRenderComponent(f, sf::Color::Black, static_cast<float>(x), static_cast<float>(y), size, s);

	mousePressButton* ic = new mousePressButton(ih, rc->getListElementBoxBounds());

	setOnPress<Desktop>(ic, &dt, func);

	entityToModify.addComponent(rc);
	entityToModify.addComponent(rc2);
	entityToModify.addComponent(ic);

}