// Rotate a sprite continually
// WARNING: No longer an applicable example when using Entities/Component
#ifndef __ROTATE_SPRITE_H__
#define __ROTATE_SPRITE_H__
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "updateComponent.h"

using namespace std;

class testRotateSprite : public ppc::UpdateComponent {

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