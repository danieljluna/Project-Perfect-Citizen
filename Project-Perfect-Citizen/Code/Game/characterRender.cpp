//
//  characterRender.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 2/28/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#include "../Engine/debug.h"
#include "characterRender.hpp"

#include <iostream>
#include <random>
#include <cassert>

#include <SFML/Graphics/RenderTarget.hpp>

using namespace ppc;

sf::Texture characterRender::texture;
bool characterRender::textureIsLoaded = false;



ppc::characterRender::characterRender() {
}

characterRender::characterRender(sf::Image& image): characterRender() {
    
    bodyScale  = 0.16f;
    eyeScale   = 0.10f;
    mouthScale = 0.08f;
    noseScale  = 0.09f;
    
    hairPos  = {18, 2 };
    eyeLPos  = {35, 33};
    eyeRPos  = {53, 33};
    browLPos = {35, 28};
    browRPos = {53, 28};
    mouthPos = {40, 55};
    nosePos =  {56, 36};

	origin.x = 0; 
	origin.y = 0;
    
    if (!textureIsLoaded) {
        sf::IntRect area(0 * grid_size,
                         0 * grid_size,
                         12 * grid_size,
                         45 * grid_size);
        if (!texture.loadFromImage(image, area)) {
            assert("COULD NOT LOAD CHARACTER RENDER TEXTURE.");
        }
    }
    
    
    initializeTones();
    shouldDraw_ = true;
    
}

ppc::characterRender & ppc::characterRender::operator=(const characterRender & other) {
	if (this != &other) {
		shouldDraw_ = other.shouldDraw_;
		scale = other.scale;

		body = other.body;
		shirt = other.shirt;
		hair = other.hair;
		irisL = other.irisL;
		irisR = other.irisR;
		eyeL = other.eyeL;
		eyeR = other.eyeR;
		browL = other.browL;
		browR = other.browR;
		mouth = other.mouth;
		nose = other.nose;

		origin = other.origin;

		skinTones = other.skinTones;
		hairTones = other.hairTones;
		lipTones = other.lipTones;

		bodyScale = other.bodyScale;
		eyeScale = other.eyeScale;
		mouthScale = other.mouthScale;
		noseScale = other.noseScale;

		hairPos = other.hairPos;
		eyeLPos = other.eyeLPos;
		eyeRPos = other.eyeRPos;
		browLPos = other.browLPos;
		browRPos = other.browRPos;
		mouthPos = other.mouthPos;
		nosePos = other.nosePos;
	}
	return *this;
}

characterRender::~characterRender() {
    //delete rectSourceSprite;
}

void ppc::characterRender::setImage(sf::Image & image) {
	bodyScale = 0.16f;
	eyeScale = 0.10f;
	mouthScale = 0.08f;
	noseScale = 0.09f;

	hairPos = { 18, 2 };
	eyeLPos = { 35, 33 };
	eyeRPos = { 53, 33 };
	browLPos = { 35, 28 };
	browRPos = { 53, 28 };
	mouthPos = { 40, 55 };
	nosePos = { 56, 36 };

	origin.x = 0;
	origin.y = 0;

	if (!textureIsLoaded) {
		sf::IntRect area(0 * grid_size,
			0 * grid_size,
			12 * grid_size,
			45 * grid_size);
		if (!texture.loadFromImage(image, area)) {
			assert("COULD NOT LOAD CHARACTER RENDER TEXTURE.");
		}
	}


	initializeTones();
	shouldDraw_ = true;

}

void characterRender::setOrigin(float x, float y){
	origin.x = x;
	origin.y = y;
}

void characterRender::applyCharacterValues(PipelineCharacter& myCharacter) {
    
    shouldDraw_ = true;
    
        
        ////////////////////////////////////
        /// DRAWING THE BODY
        ////////////////////////////////////
        body.setTexture(texture);
        body.setTextureRect(sf::IntRect(2*grid_size,
                                         0*grid_size,
                                         5*grid_size,
                                         5*grid_size));
        body.setScale(bodyScale, bodyScale);
        
        body.setColor(skinTones.at(myCharacter.getSkinColorIndex()));
        body.setPosition(origin);
        
        
        ////////////////////////////////////
        /// DRAWING THE SHIRT
        ////////////////////////////////////
        
        shirt.setTexture(texture);
    
        shirt.setTextureRect(sf::IntRect(2*grid_size,
                                          myCharacter.getShirtType()*grid_size,
                                          5*grid_size,
                                          5*grid_size));
        shirt.setScale(bodyScale, bodyScale);
        
        shirt.setColor(myCharacter.getShirtColor());
        shirt.setPosition(origin);
        
        
        ////////////////////////////////////
        /// DRAWING THE HAIR
        ////////////////////////////////////
        
        hair.setTexture(texture);
        hair.setTextureRect(sf::IntRect(7*grid_size,
                                         myCharacter.getHairType()*grid_size,
                                         3*grid_size,
                                         2*grid_size));
        hair.setScale(bodyScale, bodyScale);
        hair.setColor(hairTones.at(myCharacter.
                                        getHairColorIndex()));
        hair.setPosition(origin.x+hairPos.x, origin.y+hairPos.y);
        
        
        ////////////////////////////////////
        /// DRAWING THE EYE IRIS
        ////////////////////////////////////
        irisL.setTexture(texture);
        irisL.setTextureRect(sf::IntRect(0*grid_size,
                                          3*grid_size,
                                          grid_size,
                                          grid_size));
        irisL.setColor(myCharacter.getEyeColor());
        irisL.setPosition(origin.x + eyeLPos.x, origin.y + eyeLPos.y);
        irisL.setScale(eyeScale, eyeScale);
        
        irisR.setTexture(texture);
        irisR.setTextureRect(sf::IntRect(1*grid_size,
                                          3*grid_size,
                                          grid_size,
                                          grid_size));
        irisR.setColor(myCharacter.getEyeColor());
        irisR.setPosition(origin.x + eyeRPos.x, origin.y + eyeRPos.y);
        irisR.setScale(eyeScale, eyeScale);
        
        
        ////////////////////////////////////
        /// DRAWING THE EYES
        ////////////////////////////////////
        
        eyeL.setTexture(texture);
        eyeL.setTextureRect(sf::IntRect(0*grid_size,
                                         myCharacter.getEyeType()*grid_size,
                                         grid_size,
                                         grid_size));
        eyeL.setPosition(origin.x + eyeLPos.x, origin.y + eyeLPos.y);
        eyeL.setScale(eyeScale, eyeScale);
        
        eyeR.setTexture(texture);
        eyeR.setTextureRect(sf::IntRect(1*grid_size,
                                         myCharacter.getEyeType()*grid_size,
                                         grid_size,
                                         grid_size));
        eyeR.setPosition(origin.x + eyeRPos.x, origin.y + eyeRPos.y);
        eyeR.setScale(eyeScale, eyeScale);
        
        
        
        browR.setTexture(texture);
        browR.setTextureRect(sf::IntRect(1*grid_size,
                                          myCharacter.getBrowType()*grid_size,
                                          grid_size,
                                          grid_size));
        browR.setPosition(origin.x + browRPos.x, origin.y + browRPos.y);
        browR.setColor(hairTones.at(myCharacter.getHairColorIndex()));
        browR.setScale(eyeScale,eyeScale);
        
        
        
        browL.setTexture(texture);
        browL.setTextureRect(sf::IntRect(0*grid_size,
                                          myCharacter.getBrowType()*grid_size,
                                          grid_size,
                                          grid_size));
        browL.setPosition(origin.x + browLPos.x, origin.y + browRPos.y);
        browL.setColor(hairTones.at(myCharacter.getHairColorIndex()));
        browL.setScale(eyeScale,eyeScale);
        
        
        
        ////////////////////////////////////
        /// DRAWING THE MOUTH
        ////////////////////////////////////
        mouth.setTexture(texture);
        mouth.setTextureRect(sf::IntRect(0*grid_size,
                                          myCharacter.getMouthType()*grid_size,
                                          2*grid_size,
                                          grid_size));
        mouth.setPosition(origin.x + mouthPos.x, origin.y + mouthPos.y);
        mouth.setColor(lipTones.at(myCharacter.getLipColorIndex()));
        mouth.setScale(mouthScale, mouthScale);
        
        
        
        ////////////////////////////////////
        /// DRAWING THE NOSE
        ////////////////////////////////////
        nose.setTexture(texture);
        nose.setTextureRect(sf::IntRect(10*grid_size,
                                         myCharacter.getNoseType()*grid_size,
                                         2*grid_size,
                                         1*grid_size));
        nose.setRotation(90);
        nose.setPosition(origin.x + nosePos.x, origin.y + nosePos.y);
        
        nose.setScale(noseScale, noseScale);
    
    
}

void characterRender::initializeTones() {
    skinTones.push_back(sf::Color(255,220,177));
    skinTones.push_back(sf::Color(229,194,152));
    skinTones.push_back(sf::Color(240,216,187));
    skinTones.push_back(sf::Color(237,223,206));
    skinTones.push_back(sf::Color(237,223,206));
    skinTones.push_back(sf::Color(245,234,201));
    skinTones.push_back(sf::Color(245,234,201));
    skinTones.push_back(sf::Color(242,220,213));
    skinTones.push_back(sf::Color(235,201,171));
    
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

void characterRender::setShouldDraw(bool d) {
    shouldDraw_ = d;
}


void characterRender::draw( sf::RenderTarget& target,
                           sf::RenderStates states) const {
    if (shouldDraw_) {
        target.draw(body, states);
        target.draw(hair, states);
        target.draw(shirt, states);
        target.draw(nose, states);
        target.draw(irisL, states);
        target.draw(irisR, states);
        target.draw(eyeL, states);
        target.draw(eyeR, states);
        target.draw(browR, states);
        target.draw(browL, states);
        target.draw(mouth, states);
    }
    
    
}










