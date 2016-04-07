#include "TextBoxBuilder.h"
#include "../Engine/renderComponent.h"
#include "../Game/TextBoxInputComponent.h"
#include "../Game/TextBoxRenderComponent.h"
#include "../Game/TextFieldRenderComponent.hpp"
#include "../Engine/Entity.h"

ppc::TextBoxBuilder::TextBoxBuilder() {
	// Set defaults here
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

void ppc::TextBoxBuilder::create(Entity& e) {
	TextBoxRenderComponent* r = new TextBoxRenderComponent(*f, *c, xPos, yPos, s, stringToRender);
    r->updatePosition(xPos, yPos);
	TextBoxInputComponent* i = new TextBoxInputComponent(*ih, *r);
    TextFieldRenderComponent* fr = new TextFieldRenderComponent(xPos, yPos, 300, 36);
   
    e.addComponent(fr);
    e.addComponent(i);
	e.addComponent(r);
	

}