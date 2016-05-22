#include "TextBoxBuilder.h"

#include "../Engine/renderComponent.h"
#include "../Engine/Entity.h"
#include "../Game/TimerUpdateCmpnt.h"
#include "TextBoxInputComponent.h"
#include "TextBoxRenderComponent.h"
#include "TextFieldRenderComponent.hpp"
#include "textLabelComponent.hpp"
#include "createWindow.h"


ppc::TextBoxBuilder::TextBoxBuilder() {
	stringToRender = "DEFAULT_STRING";
	xPos = 0;
	yPos = 0;
	s = 20;

	f = nullptr;
	c = nullptr;
	ih = nullptr;
	tbi = nullptr;
	cw = nullptr;
	lim = 0;
}

ppc::TextBoxBuilder::~TextBoxBuilder() {

}

void ppc::TextBoxBuilder::setFont(sf::Font& font) {
	f = &font;
}

void ppc::TextBoxBuilder::setColor(sf::Color color) {
	c = &color;
}

void ppc::TextBoxBuilder::setPosition(sf::Vector2f vec) {
	xPos = vec.x;
	yPos = vec.y;
}

void ppc::TextBoxBuilder::setSize(int size) {
	s = size;
}

void ppc::TextBoxBuilder::setString(std::string str) {
	stringToRender = str;
}

void ppc::TextBoxBuilder::setInputHandle(ppc::InputHandler& inputHandle) {
	ih = &inputHandle;
}

void ppc::TextBoxBuilder::setContainingWindow(WindowInterface * win)
{
	cw = win;
}

void ppc::TextBoxBuilder::setTextBoxCharacterLimit(int l)
{
	lim = l;
}

void ppc::TextBoxBuilder::setIsMasked(bool m)
{
	mask = m;
}

ppc::TextBoxInputComponent * ppc::TextBoxBuilder::getTextBoxInputComponent()
{
	return tbi;
}


void ppc::TextBoxBuilder::create(Entity& e) {
	
	TimerUpdateCmpnt* tmr = new TimerUpdateCmpnt();
	TextBoxRenderComponent* r = new TextBoxRenderComponent(*f, *c, xPos+s, yPos+5, s, stringToRender);
	r->setIsMasked(mask);
	TextBoxInputComponent* i = new TextBoxInputComponent(*ih, *r, tmr, lim);
	i->setContainingWindow(cw);
    TextFieldRenderComponent* fr = new TextFieldRenderComponent(xPos, yPos, 300, 36);

	tbi = i;

	e.addComponent(fr);
	e.addComponent(r);
	e.addComponent(i);

}