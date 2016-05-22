#include "../Engine/debug.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "databaseSearchRenderComponent.h"

using namespace ppc;

const std::string TEXT_KEY_INPUT = "TKI";

databaseSearchRenderComponent::databaseSearchRenderComponent(sf::Font& f,
	int x, int y, int size) :font(f) {

	this->text = new sf::Text();

	text->setFont(font);
	text->setColor(sf::Color::Black);
	text->setPosition(float(x), float(y));
	text->setCharacterSize(size);
	text->setString("");
}


databaseSearchRenderComponent::~databaseSearchRenderComponent() {

}

void databaseSearchRenderComponent::updateString(std::string s) {
	str = s;
	text->setString(str + "|");
}

void databaseSearchRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text), states);

}

void databaseSearchRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}