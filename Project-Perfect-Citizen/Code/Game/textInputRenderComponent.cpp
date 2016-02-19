//
//  textInputRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/11/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "textInputRenderComponent.hpp"

const string TEXT_KEY_INPUT = "TKI";

textInputRenderComponent::textInputRenderComponent(sf::Font& f, 
	int x, int y, int size):font(f) {

	this->text = new sf::Text();
    
    text->setFont(font);
    text->setColor(sf::Color::White);
    text->setPosition(float(x), float(y));
    text->setCharacterSize(size);
    text->setString("");
    
}


textInputRenderComponent::~textInputRenderComponent() {
    
}

void textInputRenderComponent::updateString(string s) {
    str = s;
	text->setString(str + "|");
}

void textInputRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*(this->text), states);
}

void textInputRenderComponent::recieveMessage(msgType code) {
  
    if(code.compare(TEXT_KEY_INPUT) == 0){
        
    }
}