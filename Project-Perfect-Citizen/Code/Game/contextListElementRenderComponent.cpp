#include "contextListElementRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../Engine/event.h"
#include <iostream>

using namespace ppc;

contextListElementRenderComponent::contextListElementRenderComponent(ppc::WindowInterface* win, sf::Font f, std::string s,
	int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) {
	
	this->labelText = new sf::Text();
	labelText->setFont(font);
	labelText->setString("_default_");
	labelText->setCharacterSize(20);
	labelText->setColor(sf::Color::Black);
	labelText->setPosition(100, 100);

	contextListElementBox.setPosition(sf::Vector2f(float(boxX), float(boxY)));
	contextListElementBox.setSize(sf::Vector2f(float(boxWidth), float(boxHeight)));
	contextListElementBox.setFillColor(sf::Color(170, 170, 170));

	containingWindow = win;
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

	//Close the context menu if a release button is 
	case Event::EventTypes::sfEventType:
		if (ev.sfEvent.type == sf::Event::MouseButtonReleased) {
			containingWindow->close();
		}
		break;

		case Event::EventTypes::ButtonType:
			if (ev.buttons.state == Event::ButtonsEv::Clicked
				|| ev.buttons.state == Event::ButtonsEv::DblClicked) { 
				contextListElementBox.setFillColor(sf::Color(51, 50, 161)); }
			if (ev.buttons.state == Event::ButtonsEv::Release) { 
				contextListElementBox.setFillColor(sf::Color(170, 170, 170)); 
				containingWindow->close();
			}
			break;
		default:
			break;
	}

}

