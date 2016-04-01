#include "../Engine/debug.h"
#include "TextDisplayRenderComponent.h"


using namespace std;

TextDisplayRenderComponent::TextDisplayRenderComponent(sf::Font& f, sf::Color c,
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

TextDisplayRenderComponent::~TextDisplayRenderComponent() {
	delete text;
}

void TextDisplayRenderComponent::updatePosition(float x, float y) {
	text->setPosition(x, y);
}

void TextDisplayRenderComponent::updateSize(int s) {
	text->setCharacterSize(s);
}

void TextDisplayRenderComponent::updateString(string str) {
	labelString = str;
	text->setString(labelString);
}

void TextDisplayRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text), states);
}