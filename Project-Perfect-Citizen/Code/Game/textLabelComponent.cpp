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

textLabelComponent::textLabelComponent(sf::Font& f,sf::Color c,
                                       int x,
                                       int y,
                                       int s,
                                       string str): font(f) {
    
    this->text = new sf::Text();
    
    labelString = str;

	size_t pos = 0;

	for (int i = 0, j = 0; i < labelString.size(); ++i, ++j) {
		if (labelString.at(i) == '_' && j > 5) {
			labelString.insert(i, "\n");
			i++;
			j = 0;
		}
	}
	/*if (labelString.size() > 10) {
		while ((pos = labelString.find('_')) != string::npos) {
			labelString.insert(pos, "\n");
			cout << "ran" << endl;
		}
	}*/
    text->setFont(font);
    text->setPosition(x, y);
    text->setCharacterSize(s);
    text->setColor(c);
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
    text->setString(labelString);
}

void textLabelComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*(this->text), states);
}