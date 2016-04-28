//
//  photoRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Brandon Gomez on 3/1/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "photoRenderComponent.hpp"

using namespace ppc;

photoRenderComponent::photoRenderComponent(sf::Image& image) : image(image){
    
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image))
        exit(-1);
    
    sprite->setTexture(*texture);
    sprite->setPosition(0, 0);
    sprite->setScale(0.5f, 0.5f);
}

void photoRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*sprite, states);
}

void photoRenderComponent::setImageScale(float ScaleX, float ScaleY){
    sprite->setScale(ScaleX, ScaleY);
}
