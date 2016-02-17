//
//  textInputRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/11/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "textInputRenderComponent.hpp"

const string TEXT_KEY_INPUT = "TKI";

textInputRenderComponent::textInputRenderComponent(sf::Font& f, int x, int y, int size):font(f) {
	this->text = new sf::Text();
    
    //font.loadFromFile(resourcePath() + "Consolas.ttf");
    text->setFont(font);
    text->setColor(sf::Color::White);
    text->setPosition(x, y);
    text->setCharacterSize(size);
    text->setString("");
    
  //  this->sprite = new sf::Sprite();

    
    //sprite->setTextureRect(sf::IntRect(400, 10, 200, 16));
    //sprite->setColor(sf::Color(0,0,0));

    
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