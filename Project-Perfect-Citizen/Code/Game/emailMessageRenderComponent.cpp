#include "emailMessageRenderComponent.h"

using namespace ppc;

emailMessageRenderComponent::emailMessageRenderComponent(sf::Font& f, Email& email, int x, int y, int size) : font(f) {

	this->text = new sf::Text();
	text->setFont(font);
	text->setColor(sf::Color::Black);
	text->setPosition(float(x), float(y));
	text->setCharacterSize(size);
	
	/* Format the email text */
	std::string formattedEmail;
	formattedEmail += "To: " + email.getToField() + "\n";
	formattedEmail += "From: " + email.getFromField() + "\n";
	formattedEmail += "Subject: " + email.getSubjectField() + "\n\n";
	formattedEmail += "         " + email.getContentField() + "\n";

	text->setString(formattedEmail);
}

emailMessageRenderComponent::~emailMessageRenderComponent() {

}


void emailMessageRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text), states);
}

void emailMessageRenderComponent::recieveMessage(msgType code) {
	// Recieve messages if needed here
}