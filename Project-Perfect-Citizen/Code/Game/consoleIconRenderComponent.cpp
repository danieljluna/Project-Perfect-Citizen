#include "consoleIconRenderComponent.h"
#include "../Engine/debug.h"

using namespace std;
const string MOUSE_DOUBLE_CLICK_CODE = "MDDC";

consoleIconRenderComponent::consoleIconRenderComponent(sf::Image& image,
	int x, int y, int r) : buttonImage(image) {

	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();

	/* Check that the file exists in the path */
	if (!texture->loadFromImage(image,
		sf::IntRect(x*size, y*size, r*size, size))) {
		std::exit(-1);
	}

	sprite->setTexture(*texture);
	sprite->setPosition(0, 0);
	sprite->setScale(.5f, .5f);
}

consoleIconRenderComponent::~consoleIconRenderComponent() {
	delete texture;
	delete sprite;
}

void consoleIconRenderComponent::renderPosition(sf::Vector2f pos) {
	sprite->setPosition(pos.x, pos.y);
}

sf::Sprite*  consoleIconRenderComponent::getSprite() {
	return this->sprite;
}

void consoleIconRenderComponent::setSprite(int x, int y, int r) {
	if (!texture->loadFromImage(buttonImage,
		sf::IntRect(x*size, y*size, r*size, size))) {
		exit(-1);
	}
}

void consoleIconRenderComponent::setButtonScale(int r) {
	sprite->setScale(r + 0.0f, r + 0.0f);
}

void consoleIconRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->sprite), states);
}

void consoleIconRenderComponent::recieveMessage(msgType code) {

	if (code.compare(MOUSE_DOUBLE_CLICK_CODE) == 0)
		cout << "animate icon" << endl;
}