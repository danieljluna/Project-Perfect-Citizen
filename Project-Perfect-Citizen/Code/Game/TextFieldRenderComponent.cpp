//
//  TextFieldRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 4/6/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//
#include "../Engine/debug.h"
#include "TextFieldRenderComponent.hpp"

#include "../ResourceDef.h"

#include "TextDisplayRenderComponent.h"


using namespace ppc;

TextFieldRenderComponent::TextFieldRenderComponent(float x, float y, float w, float h) {

    bounds.left = x;
    bounds.top = y;
    bounds.width = w;
    bounds.height = h;

    box.setFillColor(sf::Color(110,110,110));
    box.setSize(sf::Vector2f(bounds.width+2, bounds.height+2));
    box.setPosition(bounds.left-2, bounds.top);
    
    shadow.setFillColor(sf::Color(90,90,90));
    shadow.setSize(sf::Vector2f(bounds.width-2, bounds.height-2));
    shadow.setPosition(bounds.left, bounds.top+2);
    
    shadow2.setFillColor(sf::Color(60,60,60));
    shadow2.setSize(sf::Vector2f(bounds.width-2, bounds.height-2));
    shadow2.setPosition(bounds.left+2, bounds.top+2);
    
    white.setFillColor(sf::Color::White);
    white.setSize(sf::Vector2f(bounds.width-4, bounds.height-4));
    white.setPosition(bounds.left+2, bounds.top+4);
    
}
TextFieldRenderComponent::~TextFieldRenderComponent() {
    
}


void TextFieldRenderComponent::draw(sf::RenderTarget& target,
                                      sf::RenderStates states) const {
  
    target.draw(box, states);
    target.draw(shadow, states);
    target.draw(shadow2, states);
    target.draw(white, states);
}