// Rotate a sprite continually
#ifndef __ROTATE_SPRITE_H__
#define __ROTATE_SPRITE_H__
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "update_component.h"

using namespace std;

class testRotateSprite : public UpdateComponent {

private:
	sf::Sprite* sprite;
	float angle;
public:
	testRotateSprite();
	testRotateSprite(sf::Sprite& sprt, float angle);
	~testRotateSprite();
	void update(sf::Time deltaTime) override;
};


#endif __ROTATE_SPRITE_H__