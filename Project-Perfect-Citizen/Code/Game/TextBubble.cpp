#include "TextBubble.h"

#include "../Engine/World.h"
#include <fstream>

void ppc::TextBubble::formatLine(std::string &) {
	//TODO
}

ppc::TextBubble::TextBubble() {

	drawable = true;

	textBox.setFillColor(sf::Color::White);
	textBox.setOutlineColor(sf::Color::Black);
	textBox.setPosition(0.f, 0.f);
	textBox.setSize({ 20.f,20.f });

	displayText.setFont(World::getFont(World::Consola));
	displayText.setString("");
	displayText.setStyle(sf::Text::Bold);
	displayText.setPosition(10.f, 10.f);

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
			textQueue.push(line);
		}

		displayText.setString(textQueue.front());
		result = true;
	}

	return result;
}

void ppc::TextBubble::progressText() {
	if (textQueue.size() <= 0) {
		drawable = false;
		displayText.setString("");
	}

	textQueue.pop();
	displayText.setString(textQueue.front());
}

void ppc::TextBubble::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	if(drawable){
		states.transform *= getTransform();
		target.draw(textBox, states);
		target.draw(displayText, states);
	}
}
