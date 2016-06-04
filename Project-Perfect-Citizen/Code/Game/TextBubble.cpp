#include "TextBubble.h"

#include "../Engine/World.h"
#include "../Engine/debug.h"


//Function used is an altered version of the function found at
// https://gist.github.com/LiquidHelium/7858095
// All credit for the creation of this code goes to its creator.
sf::String ppc::TextBubble::wrapText(sf::String string, bool bold = false) {
    unsigned width = 210;//rectBubble_.sf::Shape::getPoint(1).x-rectBubble_.sf::Shape::getPoint(0).x;//(int)rectBubble_.getSize().x;
	unsigned characterSize = displayText_.getCharacterSize();
	sf::Font font = *displayText_.getFont();
	unsigned currentOffset = 0;
	bool firstWord = true;
	std::size_t wordBegining = 0;

	for (std::size_t pos(0); pos < string.getSize(); ++pos) {
		auto currentChar = string[pos];
		if (currentChar == '\n') {
			currentOffset = 0;
			firstWord = true;
			continue;
		} else if (currentChar == ' ') {
			wordBegining = pos;
			firstWord = false;
		}

		auto glyph = font.getGlyph(currentChar, characterSize, bold);
		currentOffset += (int)glyph.advance;

		if (!firstWord && currentOffset > width) {
			pos = wordBegining;
			string[pos] = '\n';
			firstWord = true;
			currentOffset = 0;
		}
	}

	return string;
}

ppc::TextBubble::TextBubble() {
	currStr_ = "";
	displayText_.setString(currStr_);
	displayText_.setCharacterSize(13);
	displayText_.setColor(sf::Color::Black);
	displayText_.setFont(World::getFont(World::Consola));
	displayText_.setPosition({4.f,5.f});
    
    rectBubble_.setPointCount(7);
    rectBubble_.setPoint(0, sf::Vector2f(0,100));
    rectBubble_.setPoint(1, sf::Vector2f(rectBubble_.getPoint(0).x+220,rectBubble_.getPoint(0).y));
    rectBubble_.setPoint(2, sf::Vector2f(rectBubble_.getPoint(0).x+220,rectBubble_.getPoint(0).y-20));
    rectBubble_.setPoint(3, sf::Vector2f(rectBubble_.getPoint(0).x+240,rectBubble_.getPoint(0).y-30));
    rectBubble_.setPoint(4, sf::Vector2f(rectBubble_.getPoint(0).x+220,rectBubble_.getPoint(0).y-40));
    rectBubble_.setPoint(5, sf::Vector2f(rectBubble_.getPoint(0).x+220,rectBubble_.getPoint(0).y-100));
    rectBubble_.setPoint(6, sf::Vector2f(rectBubble_.getPoint(0).x,rectBubble_.getPoint(0).y-100));
	rectBubble_.setFillColor(sf::Color::White);
    rectBubble_.setOutlineColor(sf::Color::Black);
    rectBubble_.setOutlineThickness(2.f);
	rectBubble_.setPosition(0.f, 0.f);
    
	//rectBubble_.setSize({ 200.f,100.f });

}

ppc::TextBubble::~TextBubble() {

}

void ppc::TextBubble::setText(std::string s) {
	currStr_ = s;
	displayText_.setString(wrapText(currStr_));
}

sf::ConvexShape & ppc::TextBubble::getBubble() {
	return rectBubble_;
}

void ppc::TextBubble::setRectPos(sf::Vector2f pos) {
    rectPos_ = pos;
}

void ppc::TextBubble::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	states.transform *= this->getTransform();
	target.draw(rectBubble_, states);
	target.draw(displayText_, states);
}

