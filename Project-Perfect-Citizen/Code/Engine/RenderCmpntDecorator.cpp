#include "RenderCmpntDecorator.h"

using namespace ppc;

renderCmpntDecorator::renderCmpntDecorator(RenderComponent& updatePtr): 
	rCmpntHandle_(&updatePtr){}

renderCmpntDecorator:: ~renderCmpntDecorator() {
	delete rCmpntHandle_;
}

Entity* renderCmpntDecorator::getEntity() {
	return rCmpntHandle_->getEntity();
}

void renderCmpntDecorator::recieveMessage(msgType message) {
	rCmpntHandle_->recieveMessage(message);
}

void renderCmpntDecorator::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(*rCmpntHandle_, states);
}