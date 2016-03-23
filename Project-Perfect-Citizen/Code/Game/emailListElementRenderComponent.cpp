#include "emailListElementRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

emailListElementRenderComponent::emailListElementRenderComponent(sf::Font& f, Email& email, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) : font(f) {
	
	this->text = new sf::Text();
	text->setFont(font);
	text->setColor(sf::Color::Black);
	text->setPosition(float(x), float(y));
	text->setCharacterSize(size);
	text->setString(email.getSubjectField());

	emailListElementBox.setPosition(sf::Vector2f(float(boxX), float(boxY)));
	emailListElementBox.setSize(sf::Vector2f(float(boxWidth), float(boxHeight)));
	emailListElementBox.setFillColor(sf::Color::White);
	
}

emailListElementRenderComponent::~emailListElementRenderComponent() {

}

sf::FloatRect emailListElementRenderComponent::getListElementBoxBounds() {
	return emailListElementBox.getGlobalBounds();
}

void emailListElementRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(this->emailListElementBox, states);
	target.draw(*(this->text), states);
}

void emailListElementRenderComponent::recieveMessage(msgType code) {
	// Recieve messages if needed here
}