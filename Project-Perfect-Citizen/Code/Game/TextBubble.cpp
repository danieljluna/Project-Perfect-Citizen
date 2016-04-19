#include "TextBubble.h"

#include "../Engine/World.h"

#include <fstream>

void ppc::TextBubble::formatLine(std::string &) {
	//TODO
}

ppc::TextBubble::TextBubble() {
	currStr_ = "";
	displayText_.setString(currStr_);
	displayText_.setCharacterSize(11);
	displayText_.setColor(sf::Color::Black);
	displayText_.setFont(World::getFont(World::Consola));
	displayText_.setPosition({ 20.f,20.f });

	rectBubble_.setFillColor(sf::Color::White);
	rectBubble_.setPosition(0.f, 0.f);
	rectBubble_.setSize({ 200.f,150.f });

}

ppc::TextBubble::~TextBubble() {

}

void ppc::TextBubble::setText(std::string s) {
	currStr_ = s;
}

sf::RectangleShape & ppc::TextBubble::getBubble() {
	return rectBubble_;
}

void ppc::TextBubble::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	states.transform *= this->getTransform();
	target.draw(rectBubble_, states);
	target.draw(displayText_, states);
}

