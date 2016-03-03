//
//  textLabelComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/3/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//
#include "../Engine/debug.h"
#include "textLabelComponent.hpp"


using namespace std;

textLabelComponent::textLabelComponent(sf::Font& f,
                                       int x,
                                       int y,
                                       int s,
                                       string str): font(f) {
    
    this->text = new sf::Text();
    
    labelString = str;

    text->setFont(font);
    text->setPosition(x, y);
    text->setCharacterSize(s);
    text->setColor(sf::Color::Black);
    text->setString(labelString);
    
}

textLabelComponent::~textLabelComponent() {
    delete text;
}

void textLabelComponent::updateLabelPosition(float x, float y) {
    text->setPosition(x, y);
}

void textLabelComponent::updateLabelSize(int s) {
    text->setCharacterSize(s);
}

void textLabelComponent::updateLabelString(string str) {
    labelString = str;
}

void textLabelComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*(this->text), states);
}