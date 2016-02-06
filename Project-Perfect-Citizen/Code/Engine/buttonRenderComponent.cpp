#include "buttonRenderComponent.h"

using namespace std;
const int MOUSE_DOWN_CODE = 200;
const int MOUSE_RELEASED_CODE = 400;
const int MOUSE_DOUBLE_CLICK_CODE = 600;

buttonRenderComponent::buttonRenderComponent( sf::Image& image, 
	int x, int y, int r) : buttonImage(image) {
	
	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();

	/* Check that the file exists in the path */
	if (!texture->loadFromImage(image, 
		sf::IntRect(x*size, y*size, r*size, size))) { std::exit(-1); }

	sprite->setTexture(*texture);
	sprite->setPosition(0, 0);
	sprite->setScale(.5f, .5f);
}

buttonRenderComponent::~buttonRenderComponent() {
	delete texture;
	delete sprite;
}

void buttonRenderComponent::renderPosition(sf::Vector2f pos) {
	sprite->setPosition(pos.x, pos.y);
}

sf::Sprite*  buttonRenderComponent::getSprite() {
	return this->sprite;
}

void buttonRenderComponent::setSprite(int x, int y, int r) {
    if(!texture->loadFromImage(buttonImage, 
		sf::IntRect(x*size, y*size, r*size, size))) { exit(-1); }
}

void buttonRenderComponent::setButtonScale(int r) {
	sprite->setScale(r + 0.0f, r + 0.0f);
}

void buttonRenderComponent::draw( sf::RenderTarget& target, 
	sf::RenderStates states) const {
		target.draw(*(this->sprite), states);
}

void buttonRenderComponent::recieveMessage(msgType code) {
	switch (code) {
		case MOUSE_DOWN_CODE:
			setSprite(1, 3, 1);
			break;
		case MOUSE_RELEASED_CODE:
			setSprite(0, 3, 1);
			break;
		case MOUSE_DOUBLE_CLICK_CODE:
			setSprite(6, 5, 1);
			break;
		default:
			break;
	}
}