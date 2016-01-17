// Rotate a sprite continually

#pragma once

#include <SFML/Graphics.hpp>

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

