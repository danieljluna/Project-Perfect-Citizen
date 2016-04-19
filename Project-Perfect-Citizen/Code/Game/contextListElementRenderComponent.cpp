#include "contextListElementRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../Engine/event.h"
#include <iostream>

using namespace ppc;

contextListElementRenderComponent::contextListElementRenderComponent(sf::Font f,
	std::string s, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {

	this->labelText = new sf::Text();
	labelText->setFont(font);
	labelText->setString("_default_");
	labelText->setCharacterSize(20);
	labelText->setColor(sf::Color::Black);
	labelText->setPosition(100, 100);

	
	contextListElementBox.setPosition(sf::Vector2f(float(boxX), float(boxY)));
	contextListElementBox.setSize(sf::Vector2f(float(boxWidth), float(boxHeight)));
	contextListElementBox.setFillColor(sf::Color(170, 170, 170));

}

contextListElementRenderComponent::~contextListElementRenderComponent() {

}

///////////////////////////////////////////////////////////////////////
/// @brief Simple getter returning the bounds of the element box
///////////////////////////////////////////////////////////////////////
sf::FloatRect contextListElementRenderComponent::getListElementBoxBounds() {
	return contextListElementBox.getGlobalBounds();
}

void contextListElementRenderComponent::draw(sf::RenderTarget & target, 
	sf::RenderStates states) const {
	target.draw(this->contextListElementBox, states);
	target.draw(*(this->labelText), states);
}

void contextListElementRenderComponent::recieveMessage(Event ev) {
	switch (ev.type) {
		case Event::EventTypes::ButtonType:
			if (ev.buttons.isPushed) { contextListElementBox.setFillColor(sf::Color(51, 50, 161)); }
			else if (ev.buttons.isReleased) { contextListElementBox.setFillColor(sf::Color(170, 170, 170)); }
			else if (ev.buttons.isHovered) { std::cout << "Hovered!"; }
			break;
		default:
			break;
	}

}

