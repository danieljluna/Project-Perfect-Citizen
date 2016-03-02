//
//  characterRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/28/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "characterRender.hpp"
#include <iostream>
#include <random>



characterRender::characterRender(sf::Image& image): faceImage(image) {
    
    this->body = new sf::Sprite();
    this->shirt = new sf::Sprite();
    this->hair = new sf::Sprite();
    this->irisL = new sf::Sprite();
    this->irisR = new sf::Sprite();
    this->eyeL = new sf::Sprite();
	this->eyeR = new sf::Sprite();
    this->browL = new sf::Sprite();
    this->browR = new sf::Sprite();
    this->mouth = new sf::Sprite();
	this->nose = new sf::Sprite();
    this->texture = new sf::Texture();

	origin.x = 0; 
	origin.y = 0;
    
    if(!texture->loadFromImage(faceImage, sf::IntRect(0*grid_size,
                                                      0*grid_size,
                                                      12*grid_size,
                                                      10*grid_size)))
    { exit(-1);}
    
    
    initializeTones();
   }

characterRender::~characterRender() {
    delete texture;
    delete body;
    delete shirt;
    delete hair;
    delete irisL;
    delete irisR;
    delete eyeL;
    delete eyeR;
    delete mouth;
    //delete rectSourceSprite;
}

void characterRender::setOrigin(float x, float y){
	origin.x = x;
	origin.y = y;
}

void characterRender::applyCharacterValues(PipelineCharacter& myCharacter) {
    
    ////////////////////////////////////
    /// DRAWING THE BODY
    ////////////////////////////////////
    body->setTexture(*texture);
    body->setTextureRect(sf::IntRect(2*grid_size,
                                     0*grid_size,
                                     5*grid_size,
                                     5*grid_size));
    body->setScale(0.6f, 0.6f);

    body->setColor(skinTones.at(myCharacter.getSkinColorIndex()));
    body->setPosition(origin);
    
    
    ////////////////////////////////////
    /// DRAWING THE SHIRT
    ////////////////////////////////////
    
    shirt->setTexture(*texture);
    shirt->setTextureRect(sf::IntRect(2*grid_size,
                                     5*grid_size,
                                     5*grid_size,
                                     5*grid_size));
    shirt->setScale(0.6f, 0.6f);
    
    shirt->setColor(myCharacter.getShirtColor());
    shirt->setPosition(origin);
    
    
    ////////////////////////////////////
    /// DRAWING THE HAIR
    ////////////////////////////////////

    hair->setTexture(*texture);
    hair->setTextureRect(sf::IntRect(7*grid_size,
                                     0*grid_size,
                                     3*grid_size,
                                     2*grid_size));
    hair->setScale(0.6f, 0.6f);
    if (myCharacter.getHairType() == 2) {
        hair->setColor(sf::Color(0,0,0,0));
    } else {
        hair->setColor(hairTones.at(myCharacter.
                                    getHairColorIndex()));
    }
    hair->setPosition(origin.x+70, origin.y-5);
    
    
    ////////////////////////////////////
    /// DRAWING THE EYE IRIS
    ////////////////////////////////////
    irisL->setTexture(*texture);
    irisL->setTextureRect(sf::IntRect(0*grid_size,
                                      3*grid_size,
                                      grid_size,
                                      grid_size));
    irisL->setColor(myCharacter.getEyeColor());
    irisL->setPosition(origin.x + 125, origin.y + 110);
    irisL->setScale(0.4f, 0.4f);
    
    irisR->setTexture(*texture);
    irisR->setTextureRect(sf::IntRect(1*grid_size,
                                      3*grid_size,
                                      grid_size,
                                      grid_size));
    irisR->setColor(myCharacter.getEyeColor());
    irisR->setPosition(origin.x + 195, origin.y + 110);
    irisR->setScale(0.4f, 0.4f);
    
    
    ////////////////////////////////////
    /// DRAWING THE EYES
    ////////////////////////////////////
    
    eyeL->setTexture(*texture);
    eyeL->setTextureRect(sf::IntRect(0*grid_size,
                                     myCharacter.getEyeType()*grid_size,
                                     grid_size,
                                     grid_size));
    eyeL->setPosition(origin.x + 125, origin.y + 110);
    eyeL->setScale(0.4f, 0.4f);
    
    eyeR->setTexture(*texture);
    eyeR->setTextureRect(sf::IntRect(1*grid_size,
                                      myCharacter.getEyeType()*grid_size,
                                     grid_size,
                                     grid_size));
    eyeR->setPosition(origin.x + 195, origin.y + 110);
    eyeR->setScale(0.4f, 0.4f);
    
    
    
    browR->setTexture(*texture);
    browR->setTextureRect(sf::IntRect(1*grid_size,
                                      myCharacter.getBrowType()*grid_size,
                                     grid_size,
                                     grid_size));
    browR->setPosition(origin.x + 193, origin.y +76);
    browR->setColor(hairTones.at(myCharacter.getHairColorIndex()));
    browR->setScale(0.5f, 0.5f);
    
    
    
    browL->setTexture(*texture);
    browL->setTextureRect(sf::IntRect(0*grid_size,
                                       myCharacter.getBrowType()*grid_size,
                                      grid_size,
                                      grid_size));
    browL->setPosition(origin.x + 122, origin.y + 76);
    browL->setColor(hairTones.at(myCharacter.getHairColorIndex()));
    browL->setScale(0.5f, 0.5f);
    
    
    
    ////////////////////////////////////
    /// DRAWING THE MOUTH
    ////////////////////////////////////
    mouth->setTexture(*texture);
    mouth->setTextureRect(sf::IntRect(0*grid_size,
                                       myCharacter.getMouthType()*grid_size,
                                      2*grid_size,
                                      grid_size));
    mouth->setPosition(origin.x + 147, origin.y + 200);
    mouth->setColor(lipTones.at(myCharacter.getLipColorIndex()));
    mouth->setScale(0.3f, 0.3f);
    
    
    
    ////////////////////////////////////
    /// DRAWING THE NOSE
    ////////////////////////////////////
    nose->setTexture(*texture);
    nose->setTextureRect(sf::IntRect(10*grid_size,
                                       myCharacter.getNoseType()*grid_size,
                                      2*grid_size,
                                      1*grid_size));
    nose->setRotation(90);
    nose->setPosition(origin.x + 210, origin.y + 115);
    
    nose->setScale(0.35f, 0.35f);
    
    
}

void characterRender::initializeTones() {
    skinTones.push_back(sf::Color(255,220,177));
    skinTones.push_back(sf::Color(229,194,152));
    skinTones.push_back(sf::Color(228,185,143));
    skinTones.push_back(sf::Color(227,161,115));
    skinTones.push_back(sf::Color(217,145,100));
    skinTones.push_back(sf::Color(204,132, 67));
    skinTones.push_back(sf::Color(199,122, 88));
    skinTones.push_back(sf::Color(165, 67,  0));
    skinTones.push_back(sf::Color(134,  4,  0));
    skinTones.push_back(sf::Color(113,  2,  0));
    skinTones.push_back(sf::Color( 68,  0,  0));
    skinTones.push_back(sf::Color(255,224,196));
    skinTones.push_back(sf::Color(238,207,180));
    skinTones.push_back(sf::Color(222,171,127));
    skinTones.push_back(sf::Color(224,177,132));
    skinTones.push_back(sf::Color(223,166,117));
    skinTones.push_back(sf::Color(190,114, 60));
    skinTones.push_back(sf::Color(100, 25,  0));
    skinTones.push_back(sf::Color(91,   0,  0));
    skinTones.push_back(sf::Color(253,228,200));
    skinTones.push_back(sf::Color(239,214,189));
    skinTones.push_back(sf::Color(187,109, 74));
    skinTones.push_back(sf::Color(189,151,120));
    skinTones.push_back(sf::Color(225,173,164));

	hairTones.push_back(sf::Color(9, 8, 6));
	hairTones.push_back(sf::Color(44, 34, 43));
	hairTones.push_back(sf::Color(113, 99, 90));
	hairTones.push_back(sf::Color(202, 191, 177));
	hairTones.push_back(sf::Color(220, 208, 186));
	hairTones.push_back(sf::Color(255, 245, 225));
	hairTones.push_back(sf::Color(165, 107, 70));
	hairTones.push_back(sf::Color(83, 61, 50));
	hairTones.push_back(sf::Color(59, 48, 36));
	hairTones.push_back(sf::Color(85, 72, 56));
	hairTones.push_back(sf::Color(106, 78, 66));



	lipTones.push_back(sf::Color(238, 193, 173));
	lipTones.push_back(sf::Color(219, 172, 152));
	lipTones.push_back(sf::Color(210, 153, 133));
	lipTones.push_back(sf::Color(201, 130, 118));
	lipTones.push_back(sf::Color(227, 93, 106));
}




void characterRender::draw( sf::RenderTarget& target,
                           sf::RenderStates states) const {
    target.draw(*body, states);
    target.draw(*hair, states);
    target.draw(*shirt, states);
    target.draw(*nose, states);
    target.draw(*irisL, states);
    target.draw(*irisR, states);
    target.draw(*eyeL, states);
    target.draw(*eyeR, states);
    target.draw(*browR, states);
    target.draw(*browL, states);
    target.draw(*mouth, states);
    
}










