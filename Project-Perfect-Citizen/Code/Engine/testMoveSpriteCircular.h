// Move a sprite in a circular motion around a constant center 
// at a specified angular velocity
#ifndef __SPRITE_CIRCILE_H__
#define __SPRITE_CIRCILE_H__


#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "update_component.h"

using namespace std;

class testMoveSpriteCircular : public UpdateComponent {

private:
	sf::Sprite* sprite;
	sf::Vector2f circleCenter;

	float degrees;
	
	float distanceFormula(sf::Vector2f a, sf::Vector2f b);
public:
	testMoveSpriteCircular() ;
	testMoveSpriteCircular(sf::Sprite* sprt, sf::Vector2f c, float v) ;
	~testMoveSpriteCircular() ;
	void update(sf::Time deltaTime) override ;
	  
	//setters & getters here

};
#endif __SPRITE_CIRCILE_H__