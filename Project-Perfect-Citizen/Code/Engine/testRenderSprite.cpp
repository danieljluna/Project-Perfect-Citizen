#include "testRenderSprite.h"

TestRenderSprite::TestRenderSprite(string filename) {
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	//texture->loadFromFile(filename);
	texture->loadFromFile(filename);
	sprite->setTexture(*texture);
	sprite->setPosition(
            100.0 + (100.0 * (rand() % 10)), 
            100.0 + (100.0 * (rand() % 10))
        );
	sprite->setScale(.2f, .2f);
}


sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}

void TestRenderSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}


//in progress
TestRenderSprite::~TestRenderSprite() {}

