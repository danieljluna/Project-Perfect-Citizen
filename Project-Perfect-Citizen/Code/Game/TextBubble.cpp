#include "TextBubble.h"

#include "../Engine/World.h"
#include "../Game/TextDisplayRenderComponent.h"
#include "../Engine/Window.h"
#include <fstream>

void ppc::TextBubble::formatLine(std::string &) {
	//TODO
}

ppc::TextBubble::TextBubble() {
	textBox_ = new Window(225, 100, sf::Color::White);
	textBox_->setPosition(100.f, 100.f);

	buttonBuilder_.setButtonPosition(100, 50);
	buttonBuilder_.setInputHandle(textBox_->getInputHandler());
	buttonBuilder_.setLabelFont(World::getFont(World::Consola));
	buttonBuilder_.setLabelMessage("Next");
	buttonBuilder_.setSize(0.25f);
	buttonBuilder_.setLabelSize(9);
	buttonBuilder_.setSpritesByIndicies(4, 4, 1, 1);
	//need to set the spritesheet

	textBuilder_.setColor(sf::Color::Black);
	textBuilder_.setFont(World::getFont(World::Consola));
	textBuilder_.setPosition({ 10,10 });
	textBuilder_.setSize(10);

}

ppc::TextBubble::~TextBubble() {
	textDisplay_ = nullptr;
}

bool ppc::TextBubble::loadText(std::string filename) {
	std::ifstream ifs(filename);

	bool result = false;
	std::string line;

	if (ifs.is_open()) {
		while (std::getline(ifs, line)) {
			//line += "\n";
			//format line here before inserting
			textQueue_.push(line);
		}
		if (textQueue_.size() != 0) {
			currString_ = textQueue_.front();
			textBuilder_.setString(currString_);
			textQueue_.pop();
			result = true;
		}
	}

	return result;
}

void ppc::TextBubble::advanceText() {
	if (textQueue_.size() > 0) {
		currString_ = textQueue_.front();
		textDisplay_->updateString(currString_);
		textQueue_.pop();
	} else {
		currString_ = "";
		textBox_->close();
	}

}

ppc::Entity & ppc::TextBubble::getButtonEntity() {
	return bubbleButton_;
}

ppc::ButtonBuilder & ppc::TextBubble::getButtonBuilder() {
	return buttonBuilder_;
}

ppc::Window& ppc::TextBubble::getTextBox() {
	return *textBox_;
}

void ppc::TextBubble::generateBubble() {
	createWithEventFunc(buttonBuilder_, bubbleButton_, this, advanceOnPress);
	textBuilder_.create(bubbleButton_);
	size_t size = bubbleButton_.cmpntCount();
	textDisplay_ = 
		dynamic_cast<TextDisplayRenderComponent*>(bubbleButton_.getComponent(size - 1));

	textBox_->addEntity(bubbleButton_);

}



bool ppc::advanceOnPress(TextBubble* tb, ppc::Event e) {
	if (tb == nullptr) return true;

	if (e.sfEvent.type == sf::Event::MouseButtonReleased &&
		e.sfEvent.mouseButton.button == sf::Mouse::Left) {
		tb->advanceText();
	}

	return true;
}
