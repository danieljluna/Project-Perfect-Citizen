#include "../Engine/debug.h"
#include "TextDisplayRenderComponent.h"
#include <ostream>
#include "../Engine/event.h"

#ifdef WINDOWS_MARKER
    #define resourcePath() std::string("Resources/")
#else
    #include "ResourcePath.hpp"
#endif

using namespace ppc;

sf::Font TextDisplayRenderComponent::defaultFont;
bool TextDisplayRenderComponent::isLoaded = false;

TextDisplayRenderComponent::TextDisplayRenderComponent() {
    //Load default Font
    if (!isLoaded) {
        defaultFont.loadFromFile(resourcePath() + "consola.ttf");
        isLoaded = true;
    }

    labelString_ = "";

	this->text_ = new sf::Text();
	this->outline_ = new sf::Text();

    text_->setFont(defaultFont);
    text_->setPosition(0, 0);
    text_->setCharacterSize(12);
    text_->setColor(sf::Color::Black);
    text_->setString(labelString_);

	outline_->setFont(defaultFont);
	outline_->setPosition(2, 0);
	outline_->setCharacterSize(12);
	if (text_->getColor() == sf::Color::Black)
		outline_->setColor(sf::Color::White);
	else outline_->setColor(sf::Color::Black);
	outline_->setString(labelString_);

}

TextDisplayRenderComponent::TextDisplayRenderComponent(sf::Font& f, sf::Color c,
	float x,
	float y,
	unsigned int s,
	std::string str) : font_(f) {

	this->text_ = new sf::Text();
	this->outline_ = new sf::Text();

	labelString_ = str;
	
	text_->setFont(font_);
	text_->setPosition(x, y);
	text_->setCharacterSize(s);
	text_->setColor(c);
	text_->setString(labelString_);

	outline_->setFont(font_);
	outline_->setPosition(x+2, y);
	outline_->setCharacterSize(s);
	if (text_->getColor() == sf::Color::Black)
		outline_->setColor(sf::Color::White);
	else outline_->setColor(sf::Color::Black);
	outline_->setString(labelString_);

}

TextDisplayRenderComponent::~TextDisplayRenderComponent() {
}

void TextDisplayRenderComponent::updatePosition(float x, float y) {
	text_->setPosition(x, y);
}

void TextDisplayRenderComponent::updateSize(unsigned int s) {
	text_->setCharacterSize(s);
}

void TextDisplayRenderComponent::updateString(std::string str) {
	labelString_ = str;
	text_->setString(labelString_);
}

void TextDisplayRenderComponent::updateFont(sf::Font f) {
    text_->setFont(f);
}

void TextDisplayRenderComponent::updateColor(sf::Color c) {
    text_->setColor(c);
}

sf::Text* TextDisplayRenderComponent::getText() {
	return text_;
}

void TextDisplayRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void TextDisplayRenderComponent::recieveMessage(ppc::Event ev) {
	switch (ev.type) {
	case Event::EventTypes::ButtonType:
		if (ev.buttons.isPushed) {
			text_->setColor(sf::Color::White);
		}
		if (ev.buttons.isReleased) {
			text_->setColor(sf::Color::Black);
		}
		break;
	default:
		break;
	}
}