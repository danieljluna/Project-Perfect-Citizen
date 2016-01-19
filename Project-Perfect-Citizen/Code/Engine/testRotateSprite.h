// testRotateSprite.h
// Nader Sleem

// Rotate a sprite continually
// Not a good example now that we have Entities
// Ask Nader for help with update components when needed
#pragma once

#include <SFML/Graphics.hpp>

#include "updateComponent.h"

using namespace std;

class testRotateSprite : public ppc::updateComponent {

private:
	sf::Sprite* sprite;
	float angle;
public:
	testRotateSprite();
	testRotateSprite(sf::Sprite& sprt, float angle);
	~testRotateSprite();
	void update(sf::Time deltaTime) override;
};

