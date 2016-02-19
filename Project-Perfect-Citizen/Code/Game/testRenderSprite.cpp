#include "testRenderSprite.h"
#include "../Engine/debug.h"
TestRenderSprite::TestRenderSprite(sf::Image& image, int x, int y,
                                   int r) {
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();
    //texture->loadFromFile(filename);
    if (!texture->loadFromImage(image,
                                sf::IntRect(x*size, y*size, r*size,
                                            size))){
        //ERROR
        std::exit(-1);
    }
    
    
    sprite->setTexture(*texture);
    sprite->setPosition(0,0);
    sprite->setScale(.5f, .5f);
}

TestRenderSprite::~TestRenderSprite() {
	delete texture;
	delete sprite;
}

void TestRenderSprite::renderPosition(sf::Vector2f pos) {
    sprite->setPosition(pos.x, pos.y);
}


sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}

void TestRenderSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}


