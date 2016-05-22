//
//  endingAnimationRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/10/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "endingAnimationRender.hpp"
#include <random>
#include <cassert>
#include <algorithm>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using namespace ppc;

endingAnimationRender::endingAnimationRender(sf::Image& img):image(img){
    
    this->sprite = new sf::Sprite();
    this->comingSoon = new sf::Sprite();
    this->texture = new sf::Texture();
    this->comingSoonTexture = new sf::Texture();
    
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(0*size,8*size,6*size,size)))
        std::exit(-1);
    
    if (!comingSoonTexture->loadFromImage(image, sf::IntRect(0*size,9*size,6*size,size)))
        std::exit(-1);
    
    //comingSoon->setTextureRect(sf::IntRect(0*size,9*size,6*size,size));
    comingSoon->setTexture(*comingSoonTexture);
    comingSoon->setPosition(100, 400);
    comingSoon->setColor(sf::Color(0,255,0,0 ));

    rectSourceSprite = new sf::IntRect(0*size,8*size,6*size,size);

    
    sprite->setTexture(*texture);
    sprite->setColor(sf::Color::Green);
    sprite->setPosition(100, 200);
    sprite->setScale(1.0f, 1.0f);
    

    y_vals.push_back(384);
    y_vals.push_back(512);
    y_vals.push_back(640);
    y_vals.push_back(768);
    y_vals.push_back(896);
    y_vals.push_back(1024);
    
}


endingAnimationRender::~endingAnimationRender() {
    delete sprite;
    delete rectSourceSprite;
    delete texture;
    delete comingSoonTexture;
}
void endingAnimationRender::draw( sf::RenderTarget& target,
                                      sf::RenderStates states) const {
    target.draw(*sprite, states);
    target.draw(*comingSoon, states);

}
void endingAnimationRender::animate() {

    if (frame < 4) {
        rectSourceSprite->top -= 128;
    } else if(frame <= 16) {
        int y;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> pixeled(0, 4);
        y = pixeled(gen);
        
        rectSourceSprite->top = y_vals.at(y);
    } else {
        if (frame % 3 == 0)
            rectSourceSprite->top -= 128;
        else if (rectSourceSprite->top == 0) comingSoon->setColor(sf::Color(0,255,0,255));
    }
 
    
    frame++;
    
    texture->loadFromImage(image, *rectSourceSprite);
    sprite->setTexture(*texture);
}
