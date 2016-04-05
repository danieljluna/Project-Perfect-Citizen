#include "TextDisplayBuilder.h"
#include "../Engine/renderComponent.h"
#include "../Game/TextDisplayRenderComponent.h"
#include "../Engine/Entity.h"

ppc::TextDisplayBuilder::TextDisplayBuilder() {

}

ppc::TextDisplayBuilder::~TextDisplayBuilder() {

}

void ppc::TextDisplayBuilder::setFont(sf::Font& font) {
	f = &font;
}

void ppc::TextDisplayBuilder::setColor(sf::Color color) {
	c = &color;
}

void ppc::TextDisplayBuilder::setPosition(sf::Vector2f vec) {
	xPos = vec.x;
	yPos = vec.y;
}

void ppc::TextDisplayBuilder::setSize(int size) {
	s = size;
}

void ppc::TextDisplayBuilder::setString(std::string str) {
	stringToRender = str;
}

void ppc::TextDisplayBuilder::create(Entity& e) {
	TextDisplayRenderComponent* t = new TextDisplayRenderComponent(*f, *c, xPos, yPos, s, stringToRender);
	e.addComponent(t);
}