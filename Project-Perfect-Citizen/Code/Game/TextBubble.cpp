#include "TextBubble.h"

#include "../Engine/World.h"
#include <fstream>

void ppc::TextBubble::formatLine(std::string &) {
	//TODO
}

ppc::TextBubble::TextBubble() {

	drawable_ = true;

	textBox_.setFillColor(sf::Color::White);
	textBox_.setOutlineColor(sf::Color::Black);
	textBox_.setPosition(0.f, 0.f);
	textBox_.setSize({ 200.f,100.f });

	displayText_.setFont(World::getFont(World::Consola));
	displayText_.setString("");
	displayText_.setStyle(sf::Text::Regular);
	displayText_.setPosition(0.f, 0.f);
	displayText_.setColor(sf::Color::Black);
	displayText_.setScale({ 0.5f,0.5f });

}

ppc::TextBubble::~TextBubble() {

}

bool ppc::TextBubble::loadText(std::string filename) {
	std::ifstream ifs(filename);

	bool result = false;
	std::string line;

	if (ifs.is_open()) {
		while (std::getline(ifs, line)) {
			line += "\n";
			//format line here before inserting
			textQueue_.push(line);
		}
		if (textQueue_.size() != 0) {
			currString_ = textQueue_.front();
			displayText_.setString(currString_);
			textQueue_.pop();
			result = true;
		}
	}

	return result;
}

void ppc::TextBubble::advanceText() {
	if (textQueue_.size() > 0) {
		currString_ = textQueue_.front();
		displayText_.setString(currString_);
		textQueue_.pop();
	} else {
		currString_ = "";
		displayText_.setString("");
		drawable_ = false;
	}

}

void ppc::TextBubble::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	if (drawable_) {
		states.transform *= getTransform();
		target.draw(textBox_, states);
		target.draw(displayText_, states);
	}
}



bool ppc::advanceOnPress(TextBubble* tb, ppc::Event e) {
	if (tb == nullptr) return true;

	if (e.sfEvent.type == sf::Event::MouseButtonReleased &&
		e.sfEvent.mouseButton.button == sf::Mouse::Left) {
		tb->advanceText();
	}

	return true;
}
