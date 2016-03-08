//
//  bootLoadingAnimationRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "bootLoadingAnimationRender.hpp"

bootLoadingAnimationRender::bootLoadingAnimationRender(sf::Image& img, int x, int y):image(img){

    this->sprite = new sf::Sprite();
    this->sprite1 = new sf::Sprite();
    this->sprite2 = new sf::Sprite();
    this->sprite3 = new sf::Sprite();
    this->sprite4 = new sf::Sprite();
    this->sprite5 = new sf::Sprite();
    this->sprite6 = new sf::Sprite();
    this->sprite7 = new sf::Sprite();
    this->sprite8 = new sf::Sprite();
    this->sprite9 = new sf::Sprite();
    this->sprite10 = new sf::Sprite();
    this->sprite11 = new sf::Sprite();
    this->sprite12 = new sf::Sprite();
    this->sprite13 = new sf::Sprite();
    this->sprite14 = new sf::Sprite();
    this->sprite15 = new sf::Sprite();
    this->sprite16 = new sf::Sprite();
    this->sprite17 = new sf::Sprite();
    this->sprite18 = new sf::Sprite();
    this->sprite19 = new sf::Sprite();
    this->sprite20 = new sf::Sprite();
    this->sprite21 = new sf::Sprite();
    this->sprite22 = new sf::Sprite();
    this->sprite23 = new sf::Sprite();
    this->sprite24 = new sf::Sprite();
    this->sprite25 = new sf::Sprite();
    this->sprite26 = new sf::Sprite();
    this->sprite27 = new sf::Sprite();
    this->sprite28 = new sf::Sprite();
    this->sprite29 = new sf::Sprite();
    this->sprite30 = new sf::Sprite();
    
    this->spriteLoaded = new sf::Sprite();
    this->texture = new sf::Texture();
        
    /* Check that the file exists in the path */
    if (!texture->loadFromImage(image, sf::IntRect(x*128,y*128,128,128)))
        std::exit(-1);

    sprites.push_back(sprite1);
    sprites.push_back(sprite2);
    sprites.push_back(sprite3);
    sprites.push_back(sprite4);
    sprites.push_back(sprite5);
    sprites.push_back(sprite6);
    sprites.push_back(sprite7);
    sprites.push_back(sprite8);
    sprites.push_back(sprite9);
    sprites.push_back(sprite10);
    sprites.push_back(sprite11);
    sprites.push_back(sprite12);
    sprites.push_back(sprite13);
    sprites.push_back(sprite14);
    sprites.push_back(sprite15);
    sprites.push_back(sprite16);
    sprites.push_back(sprite17);
    sprites.push_back(sprite18);
    sprites.push_back(sprite19);
    sprites.push_back(sprite20);
    sprites.push_back(sprite21);
    sprites.push_back(sprite22);
    sprites.push_back(sprite23);
    sprites.push_back(sprite24);
    sprites.push_back(sprite25);
    sprites.push_back(sprite26);
    sprites.push_back(sprite27);
    sprites.push_back(sprite28);
    sprites.push_back(sprite29);
    sprites.push_back(sprite30);
    
    loadX = 0;
    
    for (int i=0; i < 30; i++) {
        sprites.at(i)->setPosition(loadX, 720);
        sprites.at(i)->setTexture(*texture);
        sprites.at(i)->setColor(sf::Color(51,53,54));
        sprites.at(i)->setScale(0.5f, 0.5f);
        loadX += 32;
    }
    
    frame = 0;
}


bootLoadingAnimationRender::~bootLoadingAnimationRender() {
    delete sprite;
    delete sprite1;
    delete sprite2;
    delete sprite3;
    delete sprite4;
    delete sprite5;
    delete sprite6;
    delete sprite7;
    delete sprite8;
    delete sprite9;
    delete sprite10;
    delete sprite11;
    delete sprite12;
    delete sprite13;
    delete sprite14;
    delete sprite15;
    delete sprite16;
    delete sprite17;
    delete sprite18;
    delete sprite19;
    delete sprite20;
    delete sprite21;
    delete sprite22;
    delete sprite23;
    delete sprite24;
    delete sprite25;
    delete sprite26;
    delete sprite27;
    delete sprite28;
    delete sprite29;
    delete sprite30;
    sprites.clear();
    delete spriteLoaded;
    //delete loadedRect;
}
void bootLoadingAnimationRender::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*sprite, states);
    target.draw(*sprite1, states);
    target.draw(*sprite2, states);
    target.draw(*sprite3, states);
    target.draw(*sprite4, states);
    target.draw(*sprite5, states);
    target.draw(*sprite6, states);
    target.draw(*sprite7, states);
    target.draw(*sprite8, states);
    target.draw(*sprite9, states);
    target.draw(*sprite10, states);
    target.draw(*sprite11, states);
    target.draw(*sprite12, states);
    target.draw(*sprite13, states);
    target.draw(*sprite14, states);
    target.draw(*sprite15, states);
    target.draw(*sprite16, states);
    target.draw(*sprite17, states);
    target.draw(*sprite18, states);
    target.draw(*sprite19, states);
    target.draw(*sprite20, states);
    target.draw(*sprite21, states);
    target.draw(*sprite22, states);
    target.draw(*sprite23, states);
    target.draw(*sprite24, states);
    target.draw(*sprite25, states);
    target.draw(*sprite26, states);
    target.draw(*sprite27, states);
    target.draw(*sprite28, states);
    target.draw(*sprite29, states);
    target.draw(*sprite30, states);
    target.draw(*spriteLoaded, states);
}

void bootLoadingAnimationRender::animate() {
    if (frame < 30) {
        sprites.at(frame)->setColor(sf::Color(195,204,207));
        frame += 1;
    } 
    
}

