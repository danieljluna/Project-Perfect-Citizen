
#include "textOutputRenderComponent.h"
#include "../Engine/debug.h"
const string TEXT_KEY_INPUT = "TKI";

textOutputRenderComponent::textOutputRenderComponent(sf::Font& f, 
	ppc::NodeState& fT, int x, int y, int size) :font_(f),fileTree_(fT) {

	this->text_ = new sf::Text();

	//font.loadFromFile(resourcePath() + "Consolas.ttf");
	text_->setFont(font_);
	text_->setColor(sf::Color::White);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	text_->setString("");

}


textOutputRenderComponent::~textOutputRenderComponent() {
	delete text_;
}

void textOutputRenderComponent::updateString(std::vector<string> cmd) {
	
	/* Print out what was just typed */
	for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) {
		str_ = str_ + " " + (*iter);
	}
	str_ = str_ + "\n";


	/* Determine what to send based on the command given */
	if (cmd.at(0) == "ls") {
		str_ = str_ + fileTree_.getDirString() + "\n";
		cout << fileTree_.getDirString() << "here" << endl;
	}
	else if (cmd.at(0) == "pwd") {
		std::vector<std::string> wd = fileTree_.getPwdVector();
		for (auto iter = wd.begin(); iter != wd.end(); ++iter) {
			str_ = str_ + (*iter);
		}
		str_ = str_ + "\n";
	}
	else if (cmd.at(0) == "clear") {
		str_.clear();
	}
	else if (cmd.at(0) == "cd" || cmd.at(0) == "make" || 
		cmd.at(0) == "mkdir" || cmd.at(0) == "decrypt" || 
		cmd.at(0) == "encrypt") {
		// Print nothing
	}
	else { 
		str_ = str_ + "Error: command '" + cmd.at(0) + 
			"' not found" + "\n"; 
	}

	/* Set the new console display */
	text_->setString(str_);
}

void textOutputRenderComponent::clearString() {
	str_.clear();
}



void textOutputRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void textOutputRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}