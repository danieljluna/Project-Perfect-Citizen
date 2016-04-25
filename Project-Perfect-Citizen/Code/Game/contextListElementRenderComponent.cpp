#include "contextListElementRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../Engine/event.h"
#include <iostream>

using namespace ppc;

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
			if (ev.buttons.isReleased) { 
				contextListElementBox.setFillColor(sf::Color(170, 170, 170)); 
				containingWindow->close();
			}
			if (ev.buttons.isHovered) { std::cout << "Hovered!"; }
			break;
		default:
			break;
	}

}

