#include "../Engine/debug.h"
#include "buttonUpdateComponent.h"

using namespace ppc;

buttonUpdateComponent::buttonUpdateComponent(buttonRenderComponent& bRC)
	: buttonToUpdate_(bRC) {
	lastPosition_ =
		sf::Vector2f(buttonToUpdate_.getSprite()->getGlobalBounds().top,
			buttonToUpdate_.getSprite()->getGlobalBounds().left);
	buttonToUpdate_.renderPosition(lastPosition_);
}


buttonUpdateComponent::~buttonUpdateComponent() {

}

void buttonUpdateComponent::setButtonPosition(sf::Vector2f newPos) {
	lastPosition_ = newPos;
}

void buttonUpdateComponent::update(sf::Time& deltaTime) {
	buttonToUpdate_.renderPosition(lastPosition_);
	std::cout << lastPosition_.x << ",  " << lastPosition_.y << endl;
}
