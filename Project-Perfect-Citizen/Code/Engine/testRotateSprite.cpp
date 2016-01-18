
#include "testRotateSprite.h"


testRotateSprite::testRotateSprite() {
	sprite = nullptr;
	this->angle = 0.f;

}


testRotateSprite::testRotateSprite(sf::Sprite& sprt, float angle) {
	sprite = &sprt;
	this->angle = angle;
}

testRotateSprite::~testRotateSprite() {
	this->sprite = nullptr;
}

void testRotateSprite::update(sf::Time deltaTime) {
	this->sprite->rotate(angle);
}