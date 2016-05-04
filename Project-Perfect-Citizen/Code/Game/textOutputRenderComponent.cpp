
#include "textOutputRenderComponent.h"
#include "createWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include "../Engine/desktop.h"
#include "../Game/TreeCommands.h"
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include "../Engine/World.h"

#include "../Engine/WindowInterface.h"
#include "../Engine/BorderDecorator.h"
#include "../Engine/ScrollBarDeco.h"

const string TEXT_KEY_INPUT = "TKI";

using namespace ppc;

textOutputRenderComponent::textOutputRenderComponent(Desktop& dt, WindowInterface* wip, sf::Image bs, sf::Font f,
	NodeState fT, textInputRenderComponent* tirc, int x, int y, int size ) : promptLine(tirc), theDesktop_(&dt), theWindow_(wip),
	buttonSheet_(bs), font_(f), fileTree_(fT) {

	numDisplayedLines = 0;

	this->text_ = new sf::Text();

	promptLine = tirc;

	text_->setFont(font_);
	text_->setColor(sf::Color::Green);
	text_->setPosition(float(x), float(y));
	text_->setCharacterSize(size);
	text_->setString("");

}


textOutputRenderComponent::~textOutputRenderComponent() {

}

void textOutputRenderComponent::updateString(std::vector<string> cmd) {
    for (int i = 0; i < cmd[0].size(); i++) {
        cmd[0][i] = tolower(cmd[0][i]);
    }
	
	/* Print out what was just typed */
	str_ = str_ + "> ";
	for (auto iter = cmd.begin(); iter != cmd.end(); ++iter) 
		str_ = str_ + " " + (*iter);
	str_ = str_ + "\n";
	++numDisplayedLines;

	/* CASE: LS*/
	if (cmd.at(0) == "ls") {
		std::vector<string> firstLsCommand;
		string ls = "ls";
		firstLsCommand.push_back(ls);
		commandFn firstLs = findFunction(ls);
		firstLs(fileTree_, firstLsCommand);

		str_ = str_ + fileTree_.getDirString();
		int numLines = std::count(str_.begin(), str_.end(), '@');
		std::replace(str_.begin(), str_.end(), '@', '\n' );
		numDisplayedLines += numLines;
	}

	/* CASE: PWD*/
	else if (cmd.at(0) == "pwd") {
		std::vector<std::string> wd = fileTree_.getPwdVector();
		for (auto iter = wd.begin(); iter != wd.end(); ++iter)
			str_ = str_ + (*iter) + "/";
		str_ = "Current Working Directory: "+ str_ + "\n";
		++numDisplayedLines;
	}

	/* CASE: OPEN*/
	else if (cmd.at(0) == "open") {
		if (cmd.size() > 2) {
			str_ = str_ + "Error: 'open' requires one parameter.\n";
			numDisplayedLines++;
		}
		if (fileTree_.getCwd()->findElement(cmd.at(1)) != nullptr) {
			string fileResourcePath = fileTree_.getCwd()->findElement(cmd.at(1))->getFileData();
			fileTree_.getCwd()->findElement(cmd.at(1))->readFile(*theDesktop_, buttonSheet_,
				cmd.at(1), fileResourcePath);
			str_ = "Opening " + cmd.at(1) + "\n";
			numDisplayedLines += 2;
			}
    }

	/* CASE: CLEAR*/
	else if (cmd.at(0) == "clear") {
		str_.clear();
		numDisplayedLines = 0;
	}

	/* CASE: CD */
	else if (cmd.at(0) == "cd") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'cd' requires one parameter.\n";
			numDisplayedLines++;
		}
		if (cmd.at(1).compare("CP") == 0) { World::quitDesktop(); }
		if (fileTree_.getCwd()->findElement(cmd.at(1)) == nullptr) {
			str_ = str_ + "Error: Directory '" + cmd.at(1) + "' not found. \n";
			numDisplayedLines++;
		}
		else {
			if (fileTree_.getCwd()->findElement(cmd.at(1))->isPasswordProtected()) {
				str_ = str_ + "Error: Directory '" + cmd.at(1)+"' is password protected. \nHint: " + fileTree_.getCwd()->findElement(cmd.at(1))->getHint();
				numDisplayedLines+=2;
			}
			std::vector<string> cdCommand;
			string cd = "cd";
			cdCommand.push_back(cd);
			cdCommand.push_back(cmd.at(1));
			commandFn newCD = findFunction(cd);
			newCD(fileTree_, cdCommand);
			numDisplayedLines++;
		}
	}

	//CASE: FLAG
	else if (cmd.at(0) == "flag" || cmd.at(0) == "Flag") {
		ppc::BaseFileType* tempBFT = this->fileTree_.getCwd()->findElement(cmd.at(1));
		if (tempBFT != nullptr) {
			std::vector<string> firstFlagCommand;
			firstFlagCommand.push_back("flag");
			firstFlagCommand.push_back(cmd.at(1));
			commandFn firstLs = findFunction("flag");
			firstLs(fileTree_, firstFlagCommand);
			str_ = str_ + " " + cmd.at(1) + " submitted for processing.";
		}
		else {
			str_ = str_ + " Unable to find " + cmd.at(1) + ".";
		}
		numDisplayedLines++;
		
		WindowInterface* fileTracker = new Window(450, 100, sf::Color::Transparent);
		spawnFileTracker(*theDesktop_, fileTracker, fileTracker->getInputHandler(), 250, 50);
		//spawnFileTracker(*theDesktop_, fileTracker, fileTracker->getInputHandler(), SuspiciousFileHolder::getSusVecElement(0), 250, 50);
		theDesktop_->addWindow(fileTracker);
		SuspiciousFileHolder::setWindow(fileTracker);
	}

	/* CASE: MKDIR */
	else if (cmd.at(0) == "mkdir") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'mkdir' requires one parameter.\n";
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

	/* CASE: MAKE */
	else if (cmd.at(0) == "make") {
		if (cmd.size() < 2) {
			str_ = str_ + "Error: 'make' requires one parameter.\n";
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

	/* CASE: DECRYPT/ENCRYPT */
	else if ( cmd.at(0) == "decrypt" || 
		cmd.at(0) == "encrypt") {
		// Do nothing currently.
	}

	/* CASE: UNLOCK */
	else if (cmd.at(0) == "unlock") {
		std::vector<string> unlockCommand;
		string unlock = "unlock";
		unlockCommand.push_back(unlock);
		unlockCommand.push_back(cmd.at(1));
		if (cmd.size() == 3) {
			unlockCommand.push_back(cmd.at(2));
		}
        else {
            str_ = str_ + "Please enter: unlock [directory] [password].\n";
            numDisplayedLines++;
        }
		commandFn newCommand = findFunction(unlock);
		newCommand(fileTree_, unlockCommand);
        if (fileTree_.getCwd()->findElement(cmd.at(1)) == nullptr) {
            str_ = str_ + "Error: Directory '" + cmd.at(1) + "' not found. \n";
        }
		else if (fileTree_.getCwd()->findElement(cmd.at(1))->isPasswordProtected()) {
			str_ = str_ + "Access denied.\n";
		}
        //else if (!fileTree_.getCwd()->findElement(cmd.at(1))->isPasswordProtected()) {
            //str_ = str_ + "Directory not locked.\n";
        //}
		else {
			str_ = str_ + "Access granted.\n";
		}
		numDisplayedLines+= 2;
	}
    
    /* CASE: HELP*/
    else if (cmd.at(0) == "help") {
        str_ = str_ + "help                       basic help for commands\n";
        str_ = str_ + "pwd                        prints the working directory\n";
        str_ = str_ + "cd [path]                  changes the current directory\n";
        str_ = str_ + "make [filename] [content]  creates a new text file\n";
        str_ = str_ + "mkdir [name]               creates a new directory\n";
        str_ = str_ + "unlock [name] [password]   attempts to open a locked directory\n";
        str_ = str_ + "ls                         lists the contents of the current\n";
        str_ = str_ + "                           working directory\n";
        numDisplayedLines+= 8;
    }

	/* CASE: DEFAULT*/
	else { 
		str_ = str_ + "Error: command '" + cmd.at(0) + 
			"' not found." + "\n"; 
		numDisplayedLines++;
	}

	/* Set the new console display */
	if (numDisplayedLines > maxDisplayedLines) {
		
		sf::FloatRect viewRect = {
			0.0f,
			float((promptLine->getText()->getPosition().y) - (theWindow_->getView().getSize().y - 300)),
			float(theWindow_->getBounds().width),
			float(theWindow_->getBounds().height)
		};
		//dynamic_cast<ScrollBarDecorator*>(theWindow_)->move(0, numDisplayedLines - maxDisplayedLines);
		theWindow_->setView(sf::View(viewRect));
	}
	text_->setString(str_);
}

void textOutputRenderComponent::updatePrompt() {
	std::vector<std::string> pwd_vector = fileTree_.getPwdVector();
	string pwd = "C:/";

	for (auto iter = pwd_vector.begin() + 1; iter != pwd_vector.end(); ++iter) {
		pwd += *iter;
		pwd.push_back('/');
	}
	promptLine->updatePrompt(pwd);
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

sf::Text* textOutputRenderComponent::getText() {
	return text_;
}



void textOutputRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->text_), states);
}

void textOutputRenderComponent::recieveMessage(msgType code) {

	if (code.compare(TEXT_KEY_INPUT) == 0) {

	}
}