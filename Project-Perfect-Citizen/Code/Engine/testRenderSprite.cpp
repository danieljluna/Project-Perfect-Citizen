#include "testRenderSprite.h"

TestRenderSprite::TestRenderSprite(string filename) {
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	//texture->loadFromFile(filename);
	texture->loadFromFile(filename);
	sprite->setTexture(*texture);
	sprite->setPosition(100, 100);
	sprite->setScale(.2f, .2f);
	RenderComponent::renderVector.push_back(this->sprite);
}
//defining render which is an virtual function
void TestRenderSprite::render(sf::RenderWindow* wnd) {
	wnd->draw(*(this->sprite));
}

sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}