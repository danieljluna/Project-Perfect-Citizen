//
//  textInputRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/11/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "textInputRenderComponent.hpp"

const string TEXT_KEY_INPUT = "TKI";

textInputRenderComponent::textInputRenderComponent(ppc::NodeState fT, sf::Font& f, 
	int x, int y, int size): fileTree_(fT), font(f) {

	this->textSize_ = size;
	this->text = new sf::Text();
    
    text->setFont(font);
    text->setColor(sf::Color::Green);
    text->setPosition(float(x), float(y));
    text->setCharacterSize(size);
    text->setString("");
    
}


textInputRenderComponent::~textInputRenderComponent() {
    
}

void textInputRenderComponent::updateString(string s) {
	str = s;
	std::vector<std::string> pwd_vector = fileTree_.getPwdVector();
	string pwd = "C:/";

	for (auto iter = pwd_vector.begin() + 1; iter != pwd_vector.end(); ++iter) {
		pwd += *iter;
		pwd.push_back('/');
	}
	str = pwd + str;
	text->setString(str + "|");
}

void textInputRenderComponent::updatePosition(float textDisplayHeight, float offset) {
	this->text->setPosition(text->getPosition().x, textDisplayHeight);
}

sf::Text* textInputRenderComponent::getText() {
	return text;
}

void textInputRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*(this->text), states);
}

void textInputRenderComponent::recieveMessage(msgType code) {
  
    if(code.compare("UPDATEPROMPT") == 0){
		updateString("> ");
    }
}