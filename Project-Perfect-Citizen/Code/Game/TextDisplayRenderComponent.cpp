#include "../Engine/debug.h"
#include "TextDisplayRenderComponent.h"

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
    text_.setFont(defaultFont);
    text_.setPosition(0, 0);
    text_.setCharacterSize(12);
    text_.setColor(sf::Color{ 0,0,0 });
    text_.setString(labelString_);

}



TextDisplayRenderComponent::TextDisplayRenderComponent(sf::Font& f, sf::Color c,
	float x,
	float y,
	unsigned int s,
	std::string str) : font_(f) {

    //Load default Font
    if (!isLoaded) {
        defaultFont.loadFromFile(resourcePath() + "consola.ttf");
        isLoaded = true;
    }

	labelString_ = str;
	
	text_.setFont(font_);
	text_.setPosition(x, y);
	text_.setCharacterSize(s);
	text_.setColor(c);
	text_.setString(labelString_);

}

TextDisplayRenderComponent::~TextDisplayRenderComponent() {
}

void TextDisplayRenderComponent::updatePosition(float x, float y) {
	text_.setPosition(x, y);
}

void TextDisplayRenderComponent::updateSize(unsigned int s) {
	text_.setCharacterSize(s);
}

void TextDisplayRenderComponent::updateString(std::string str) {
	labelString_ = str;
	text_.setString(labelString_);
}

void TextDisplayRenderComponent::updateFont(sf::Font f) {
    text_.setFont(f);
}

void TextDisplayRenderComponent::updateColor(sf::Color c) {
    text_.setColor(c);
}

void TextDisplayRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(text_, states);
}