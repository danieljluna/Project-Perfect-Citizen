
#include "textOutputRenderComponent.h"
#include "createWindow.h"
#include "Quitter.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/NodeState.h"
#include "../Game/TreeCommands.h"
#include <string>
#include <algorithm>

const string TEXT_KEY_INPUT = "TKI";

using namespace ppc;

textOutputRenderComponent::textOutputRenderComponent(ppc::Desktop& dt, sf::Image& bs, sf::Font& f,
	ppc::NodeState& fT, int x, int y, int size) :font_(f),fileTree_(fT), theDesktop_(dt), buttonSheet_(bs) {

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
	//printVector(cmd);

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

	
		cout << fileTree_.getDirString() << endl;
		str_ = str_ + fileTree_.getDirString() + "\n";
		int numLines = std::count(str_.begin(), str_.end(), '@');
		std::replace(str_.begin(), str_.end(), '@', '\n');
		numDisplayedLines += numLines + 1;
	}
	else if (cmd.at(0) == "pwd") {
		std::vector<std::string> wd = fileTree_.getPwdVector();
		for (auto iter = wd.begin(); iter != wd.end(); ++iter) {
			str_ = str_ + (*iter) + "/";
		}
		str_ = str_ + "\n";
		++numDisplayedLines;
	}
    else if (cmd.at(0) == "open") {
        if(cmd.size() > 2){
            // do nothing
        }
        string fileResourcePath = fileTree_.getCwd()->findElement(cmd.at(1))->getFileData();
        cout << fileResourcePath << endl;
        fileTree_.getCwd()->findElement(cmd.at(1))->readFile(theDesktop_, buttonSheet_, fileResourcePath);
        numDisplayedLines++;
    }
	else if (cmd.at(0) == "clear") {
		str_.clear();
		numDisplayedLines = 0;
	}
	else if (cmd.at(0) == "cd") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'cd' requires one parameter\n";
			numDisplayedLines++;
		}
		if (cmd.at(1).compare("CP") == 0) { quitSection(); }
		else {
			std::vector<string> cdCommand;
			string cd = "cd";
			cdCommand.push_back(cd);
			cdCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(cd);
			newCD(fileTree_, cdCommand);
			numDisplayedLines++;
		}
		
	}
	else if (cmd.at(0) == "mkdir") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'mkdir' requires one parameter\n";
			numDisplayedLines++;
		}
		else {
			std::vector<string> mkdirCommand;
			string mkdir = "mkdir";
			mkdirCommand.push_back(mkdir);
			mkdirCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(mkdir);
			newCD(fileTree_, mkdirCommand);
			numDisplayedLines++;
		}
		
	}
	else if (cmd.at(0) == "make") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'make' requires one parameter\n";
			numDisplayedLines++;
		}
		else {
			std::vector<string> makeCommand;
			string make = "make";
			makeCommand.push_back(make);
			makeCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(make);
			newCD(fileTree_, makeCommand);
			numDisplayedLines++;
		}
		
	}
	else if ( 
		cmd.at(0) == "decrypt" || cmd.at(0) == "encrypt") {
		std::cout << "what..." << std::endl;
	}
	else if (cmd.at(0) == "unlock") {
		//std::cout << "ya made the right choice" << std::endl;
		/*
		std::vector<string> mkdirCommand;
		string mkdir = "mkdir";
		mkdirCommand.push_back(mkdir);
		mkdirCommand.push_back(cmd.at(1));
		commandFn newCD = findFunction(mkdir);
		newCD(fileTree_, mkdirCommand);
		numDisplayedLines++;
		*/
		std::vector<string> unlockCommand;
		string unlock = "unlock";
		unlockCommand.push_back(unlock);
		unlockCommand.push_back(cmd.at(1));
		if (cmd.size() == 3) {
			unlockCommand.push_back(cmd.at(2));
		}
		commandFn newCommand = findFunction(unlock);
		newCommand(fileTree_, unlockCommand);
		numDisplayedLines++;
	}
	else { 
		str_ = str_ + "Error: command '" + cmd.at(0) + 
			"' not found" + "\n"; 
		numDisplayedLines++;
	}

	/* Set the new console display */
	if (numDisplayedLines > maxDisplayedLines) {
		// Adjust the output to scroll or move text up here
	}
	text_->setString(str_);
}

int textOutputRenderComponent::getNumLines() {
	return numDisplayedLines;
}

void textOutputRenderComponent::clearString() {
	str_.clear();
}

sf::Vector2f textOutputRenderComponent::getPosition() const {
    return text_->getPosition();
}



void textOutputRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void textOutputRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}