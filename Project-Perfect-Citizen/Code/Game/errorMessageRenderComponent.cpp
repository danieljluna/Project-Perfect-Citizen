#include "errorMessageRenderComponent.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

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

sf::Text * ppc::errorMessageRenderComponent::getText() { return this->text; }


void errorMessageRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text), states);
}

void errorMessageRenderComponent::recieveMessage(msgType code) {
	// Recieve messages if needed here
}