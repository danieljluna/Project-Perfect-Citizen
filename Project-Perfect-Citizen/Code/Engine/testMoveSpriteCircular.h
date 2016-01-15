// Move a sprite in a circular motion around a constant center 
// at a specified angular velocity

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

	float angularVelocity;
	
	float distanceFormula(sf::Vector2f a, sf::Vector2f b);
public:
	testMoveSpriteCircular() {};
	testMoveSpriteCircular(sf::Sprite* sprt, sf::Vector2f c, float v) {};
	~testMoveSpriteCircular() {};
	void update(sf::Time deltaTime) override {};
	  
	//setters & getters here

};