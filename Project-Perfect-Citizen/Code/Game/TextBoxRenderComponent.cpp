#include "../Engine/debug.h"
#include "TextBoxRenderComponent.h"


using namespace std;

TextBoxRenderComponent::TextBoxRenderComponent(sf::Font& f, sf::Color c,
	float x,
	float y,
	int s,
	string str) : font(f) {

	this->text = new sf::Text();

	labelString = str;

	text->setFont(font);
	text->setPosition(x, y);
	text->setCharacterSize(s);
	text->setColor(c);
    text->setString(labelString);

}

TextBoxRenderComponent::~TextBoxRenderComponent() {
	delete text;
}

void TextBoxRenderComponent::updatePosition(float x, float y) {
	text->setPosition(x, y);
}

void TextBoxRenderComponent::updateSize(int s) {
	text->setCharacterSize(s);
}

void TextBoxRenderComponent::updateString(string str) {
	labelString = str;
	text->setString(labelString);
}

void TextBoxRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*text, states);
}