
#include "textOutputRenderComponent.h"

const string TEXT_KEY_INPUT = "TKI";

textOutputRenderComponent::textOutputRenderComponent(sf::Font& f, 
	ppc::NodeState& fT, int x, int y, int size) :font_(f),fileTree_(fT) {

	numDisplayedLines = 0;

	this->text_ = new sf::Text();

	//font.loadFromFile(resourcePath() + "Consolas.ttf");
	text_->setFont(font_);
	text_->setColor(sf::Color::White);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	text_->setString("");

}


textOutputRenderComponent::~textOutputRenderComponent() {

}

void textOutputRenderComponent::updateString(std::vector<string> cmd) {
	
	/* Print out what was just typed */
	str_ = str_ + "> ";
	for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) {
		str_ = str_ + " " + (*iter);
	}
	str_ = str_ + "\n";
	++numDisplayedLines;


	/* Determine what to send based on the command given */
	if (cmd.at(0) == "ls") {
		std::vector<string> firstLsCommand;
		string ls = "ls";
		firstLsCommand.push_back(ls);
		commandFn firstLs = findFunction(ls);
		firstLs(fileTree_, firstLsCommand);
		
		str_ = str_ + fileTree_.getDirString() + "\n";
		int numLines = std::count(str_.begin(), str_.end(), '@');
		std::replace(str_.begin(), str_.end(), '@', '\n');
		numDisplayedLines += numLines;
	}
	else if (cmd.at(0) == "pwd") {
		std::vector<std::string> wd = fileTree_.getPwdVector();
		for (auto iter = wd.begin(); iter != wd.end(); ++iter) {
			str_ = str_ + (*iter);
		}
		str_ = str_ + "\n";
		++numDisplayedLines;
	}
	else if (cmd.at(0) == "clear") {
		str_.clear();
		numDisplayedLines = 0;
	}
	else if (cmd.at(0) == "cd" || cmd.at(0) == "make" || 
		cmd.at(0) == "mkdir" || cmd.at(0) == "decrypt" || 
		cmd.at(0) == "encrypt") {
		// Print nothing
	}
	else { 
		str_ = str_ + "Error: command '" + cmd.at(0) + 
			"' not found" + "\n"; 
		++numDisplayedLines;
	}

	/* Set the new console display */
	text_->setString(str_);
	cout << "NUM LINES DISPLAYED CURRENTLY: " << numDisplayedLines << endl;
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