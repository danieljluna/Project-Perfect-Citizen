#include "testRenderSprite.h"

TestRenderSprite::TestRenderSprite(string filename) {
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	//texture->loadFromFile(filename);
	texture->loadFromFile(filename);
	sprite->setTexture(*texture);
	sprite->setPosition(
            100.0 + (100.0 * RenderComponent::renderVector.size()), 
            100.0 + (100.0 * RenderComponent::renderVector.size())
        );
	sprite->setScale(.2f, .2f);
	RenderComponent::renderVector.push_back(this);
	vectorIndex = RenderComponent::renderVector.size() - 1;
}


sf::Sprite*  TestRenderSprite::getSprite() {
	return this->sprite;
}

void TestRenderSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}

int TestRenderSprite::getVectorIndex()
{
	return this->vectorIndex;
}

//in progress
TestRenderSprite::~TestRenderSprite() {
	RenderComponent::renderVector.erase(RenderComponent::renderVector.begin() + this->vectorIndex);
}

