//
//  characterRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/28/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "characterRender.hpp"


characterRender::characterRender(sf::Image& image): faceImage(image) {
    
    this->irisL = new sf::Sprite();
    this->irisR = new sf::Sprite();
    this->eyeL = new sf::Sprite();
    this->eyeR = new sf::Sprite();
    
    this->texture = new sf::Texture();
    
    if(!texture->loadFromImage(faceImage, sf::IntRect(0,0,3*grid_size,6*grid_size))) { exit(-1);}
    
    generateCharacterEye();
}

characterRender::~characterRender() {
    delete texture;
    delete irisL;
    delete irisR;
    delete eyeL;
    delete eyeR;
    //delete rectSourceSprite;
}
void characterRender::generateCharacterEye(){
  
    
    int eyeType = generateEyeType();
    sf::Color eyeColor = generateEyeColor();
    
    
    ////////////////////////////////////
    /// DRAWING THE IRIS (COLOR) OF EYE
    ////////////////////////////////////

    irisL->setTexture(*texture);
    irisL->setTextureRect(sf::IntRect(0,3*grid_size,grid_size,grid_size));
    irisL->setColor(eyeColor);
    irisL->setPosition(300, 300);
    
    irisR->setTexture(*texture);
    irisR->setTextureRect(sf::IntRect(1*grid_size,3*grid_size,grid_size,grid_size));
    irisR->setColor(eyeColor);
    irisR->setPosition(450,300);
    
    
    ////////////////////////////////////
    /// DRAWING THE EYES
    ////////////////////////////////////
    
    eyeL->setTexture(*texture);
    eyeL->setTextureRect(sf::IntRect(0,eyeType*grid_size,grid_size,grid_size));
    eyeL->setPosition(300, 300);
    
    eyeR->setTexture(*texture);
    eyeR->setTextureRect(sf::IntRect(1*grid_size,eyeType*grid_size,grid_size,grid_size));
    eyeR->setPosition(450, 300);
    
    

}


void characterRender::draw( sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(*irisL, states);
    target.draw(*irisR, states);
    target.draw(*eyeL, states);
    target.draw(*eyeR, states);
}


sf::Color characterRender::generateEyeColor() {
    
    srand(time(NULL));
    
    int r = rand() % 250 + 100;
    int g = rand() % 250 + 100;
    int b = rand() % 250 + 100;
    
    sf::Color c(r,g,b);
    return c;
    
}

int characterRender::generateEyeType() {
    srand(time(NULL));
    int t = rand() % 3;
    return t;
}










