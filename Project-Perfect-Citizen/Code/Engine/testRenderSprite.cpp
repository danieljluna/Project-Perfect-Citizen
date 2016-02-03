#include "testRenderSprite.h"

TestRenderSprite::TestRenderSprite(sf::Image& image, int x, int y, int r) {
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();
    //texture->loadFromFile(filename);
    if (!texture->loadFromImage(image,
                                sf::IntRect(x*128, y*128, r*128, 128))) {
        //ERROR
        std::exit(-1);
    }


	sprite->setTexture(*texture);
	sprite->setPosition(0,0);
	sprite->setScale(.5f, .5f);
}


sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}

void TestRenderSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}


//in progress
TestRenderSprite::~TestRenderSprite() {}

