//
//  bootLoadingAnimationRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 3/7/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "bootLoadingAnimationRender.hpp"
#include "../Engine/World.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <math.h>
#include "textLabelComponent.hpp"

using namespace ppc;

bootLoadingAnimationRender::bootLoadingAnimationRender(sf::Image& img,textLabelComponent& l, int x, int y):image(img), textLabel(l){

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

    this->dcps = new sf::Sprite();
    
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
    opacity = 255;
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
    delete dcps;
    delete spriteLoaded;
    delete texture;
    sprites.clear();
    
    //delete loadedRect;
}
void bootLoadingAnimationRender::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {

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
    target.draw(*dcps, states);
    target.draw(*sprite, states);
}

std::string bootLoadingAnimationRender::getRandomString(int stringLength) {
    std::string text = "";
    std::string possible = "ABCDEFGHIJKLMNOPQRST!@#$%^&*/_+=UVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < stringLength; ++i) {
        text += possible[int(floor(rand() % possible.length()))];
    }
    return text;
}


void bootLoadingAnimationRender::animate() {
    if (frame < 29) {
        sprites.at(frame)->setColor(sf::Color::Green);
        std::string temp = textLabel.getString();
        textLabel.updateLabelString(temp + getRandomString(90) + "\n");

        frame += 1;
    } else if (frame == 29){
        for (int i = 0; i < 30; i++) {
            sprites.at(i)->setColor(sf::Color(0,0,0,0));
        }
        /*textLabel.updateLabelString("");
         texture->loadFromImage(image,sf::IntRect(0,0,1022,1024));
        sprite->setTextureRect(sf::IntRect(0,6*128,6*128,128));
        sprite->setColor(sf::Color(255,255,255,opacity));
        sprite->setTexture(*texture);
        sprite->setPosition(100, 100);
        
        dcps->setColor(sf::Color(255,255,255,opacity));
        dcps->setPosition(350, 300);
        dcps->setTextureRect(sf::IntRect(6*128,6*128,128,128));
        dcps->setTexture(*texture);
        dcps->setScale(2.0f, 2.0f);*/
        
        frame += 1;
    } else {
        
         ppc::World::quitDesktop();
        
    }/*else if (frame < 61) {
        if (opacity != 0) opacity -= 8;
        sprite->setColor(sf::Color(255,255,255,opacity));
        dcps->setColor(sf::Color(255,255,255,opacity));
        frame +=1;
    } else  if (frame < 69){
        opacity = 0;
        sprite->setColor(sf::Color(255,255,255,opacity));
        dcps->setColor(sf::Color(255,255,255,opacity));
       
       frame +=1;
    }
    
    else {
        
    } */
}

