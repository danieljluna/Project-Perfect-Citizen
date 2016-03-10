#include "errorMessageRenderComponent.h"

using namespace ppc;

errorMessageRenderComponent::errorMessageRenderComponent(sf::Font& f, std::string msg, int x, int y, int size) : font(f) {

	this->text = new sf::Text();
	text->setFont(font);
	text->setColor(sf::Color::Black);
	text->setPosition(float(x), float(y));
	text->setCharacterSize(size);
	text->setString(msg);
}

errorMessageRenderComponent::~errorMessageRenderComponent() {

}


void errorMessageRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text), states);
}

void errorMessageRenderComponent::recieveMessage(msgType code) {
	// Recieve messages if needed here
}