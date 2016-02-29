
#include "databaseDisplayRenderComponent.h"

const string TEXT_KEY_INPUT = "TKI";

databaseDisplayRenderComponent::databaseDisplayRenderComponent(sf::Font& f,
	int x, int y, int size) :font_(f) {

	this->text_ = new sf::Text();

	//font.loadFromFile(resourcePath() + "Consolas.ttf");
	text_->setFont(font_);
	text_->setColor(sf::Color::Black);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	text_->setString("");

}


databaseDisplayRenderComponent::~databaseDisplayRenderComponent() {

}

void databaseDisplayRenderComponent::updateString(std::vector<string> cmd) {
	/* Print out what was just typed */
	string output = "";
	for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) {
		output.append(*iter);
	}
	// STUB: LOOP OVER THE VECTOR YOU JUST GOT AND PRINT IT OUT
	text_->setString(output);
}

void databaseDisplayRenderComponent::clearString() {
	str_.clear();
}



void databaseDisplayRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void databaseDisplayRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}