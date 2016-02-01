#include "testRenderSprite.h"

TestRenderSprite::TestRenderSprite(string filename) {
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();
    //texture->loadFromFile(filename);
    if (!texture->loadFromFile(filename)) {
        //ERROR
        std::exit(-1);
    }
	sprite->setTexture(*texture);
	sprite->setPosition(0,0);
	sprite->setScale(.1f, .1f);
}


sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}

void TestRenderSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}


//in progress
TestRenderSprite::~TestRenderSprite() {}

