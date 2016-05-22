#include "emailListElementRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Email.h"

using namespace ppc;
const std::string SELECT_EMAIL = "SE";
const std::string DESELECT_EMAIL = "DSE";

emailListElementRenderComponent::emailListElementRenderComponent(sf::Font& f, Email* email, int boxX, int boxY, int boxWidth, int boxHeight, int x, int y, int size) : font(f) {
	
	x += 128;

	this->subjectText = new sf::Text();
	subjectText->setFont(font);
	subjectText->setColor(sf::Color::Black);
	subjectText->setPosition(float(x), float(y));
	subjectText->setCharacterSize(size);
	subjectText->setString(email->getAbbrevSubjectField());

	this->fromText = new sf::Text();
	fromText->setFont(font);
	fromText->setColor(sf::Color(127,127,127, 255));
	fromText->setPosition(float(x+indent), float(y+size));
	fromText->setCharacterSize(size-4);
	fromText->setString(email->getFromField());

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
	target.draw(*(this->subjectText), states);
	target.draw(*(this->fromText), states);
}

void emailListElementRenderComponent::recieveMessage(msgType code) {
	if (code == SELECT_EMAIL) {
		emailListElementBox.setFillColor(sf::Color::Blue);
		subjectText->setColor(sf::Color::White);
	}
	if (code == DESELECT_EMAIL) {
		emailListElementBox.setFillColor(sf::Color::White);
		subjectText->setColor(sf::Color::Black);
	}
}