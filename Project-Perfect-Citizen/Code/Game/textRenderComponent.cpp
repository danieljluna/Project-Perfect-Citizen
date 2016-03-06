//
//  textRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/2/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "textRenderComponent.hpp"

using namespace ppc;

textRenderComponent::textRenderComponent(sf::Font& f, std::string content, int x, int y, int size):font(f) {
    this->text = new sf::Text();
    text->setFont(font);
    text->setColor(sf::Color::Black);
    text->setPosition(float(x), float(y));
    text->setCharacterSize(size);
    text->setString(content);
}

textRenderComponent::~textRenderComponent() {
    
}

void textRenderComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*(this->text), states);
}