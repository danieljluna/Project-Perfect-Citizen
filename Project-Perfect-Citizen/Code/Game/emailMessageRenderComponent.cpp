#include "emailMessageRenderComponent.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

emailMessageRenderComponent::emailMessageRenderComponent(sf::Font& f, Email* email, int x, int y, int size,
	int winWidth, int winHeight) : font(f) {

	this->metaText = new sf::Text();
	metaText->setFont(font);
	metaText->setColor(sf::Color::Black);
	metaText->setPosition(float(x), float(y));
	metaText->setCharacterSize(size);

	this->contentText = new sf::Text();
	contentText->setFont(font);
	contentText->setColor(sf::Color::Black);
	contentText->setCharacterSize(size-1);

	/* Format the email meta text */
	std::string formattedMeta;
	formattedMeta += "To: " + email->getToField() + "\n";
	formattedMeta += "From: " + email->getFromField() + "\n";
	formattedMeta += "Subject: " + email->getSubjectField() + "\n\n";
	metaText->setString(formattedMeta);
	

	/* Format the email content text */
	std::string formattedContent;
	formattedContent += "         " + email->getContentField() + "\n";
	
	int lineCount = 0;
	for (size_t i = 0; i < formattedMeta.size(); ++i) {
		if (formattedMeta.at(i) == '\n') ++lineCount;
	}

	contentText->setString(formattedContent);
	contentText->setPosition(0, float(lineCount*size));

	emailContentBox.setPosition(sf::Vector2f(0.0f, float(lineCount*size)));
	emailContentBox.setFillColor(sf::Color::White);
	emailContentBox.setSize(sf::Vector2f(float(winWidth+size), float(winHeight-100)));
}

emailMessageRenderComponent::~emailMessageRenderComponent() {
}


void emailMessageRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(this->emailContentBox, states);
	target.draw(*(this->metaText), states);
	target.draw(*(this->contentText), states);
}

void emailMessageRenderComponent::recieveMessage(msgType code) {
	// Recieve messages if needed here
}