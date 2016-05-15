//
//  spriteRenderComponent.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 4/8/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "spriteRenderComponent.hpp"


spriteRenderComponent::spriteRenderComponent(sf::Image& i, float x, float y, float w, float h):image(i) {
    this->sprite = new sf::Sprite();
    this->texture = new sf::Texture();
    

    texture->setRepeated(true);
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(x*size,y*size,w*size,h*size)))
        std::exit(-1);
    
    sprite->setTexture(*texture);
    sprite->setTextureRect(sf::IntRect(x*size,y*size,w*size,h*size));
    sprite->setPosition(0, 0);
    sprite->setScale(1.f, 1.f);

}

void spriteRenderComponent::setRenderScale(sf::Vector2f vec) {
    sprite->setScale(vec.x, vec.y);
}

void spriteRenderComponent::setRenderPosition(sf::Vector2f vec){
    sprite->setPosition(vec.x, vec.y);
}

spriteRenderComponent::~spriteRenderComponent() {
    delete sprite;
    delete texture;
}

void spriteRenderComponent::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*sprite, states);
}