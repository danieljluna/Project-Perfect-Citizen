#include "debug.h"
#include "RenderCmpntDecorator.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ppc;

renderCmpntDecorator::renderCmpntDecorator(RenderComponent& updatePtr): 
	rCmpntHandle_(&updatePtr){
	
}

renderCmpntDecorator:: ~renderCmpntDecorator() {
	delete rCmpntHandle_;
}

Entity* renderCmpntDecorator::getEntity() {
	return rCmpntHandle_->getEntity();
}

void renderCmpntDecorator::setEntity(Entity* e) {
	rCmpntHandle_->setEntity(e);
}

void renderCmpntDecorator::recieveMessage(msgType message) {
	rCmpntHandle_->recieveMessage(message);
}

void renderCmpntDecorator::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {

	target.draw(*rCmpntHandle_, states);
}