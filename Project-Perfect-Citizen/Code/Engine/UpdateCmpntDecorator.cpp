#include "debug.h"
#include "UpdateCmpntDecorator.h"
#include <SFML/System/Time.hpp>

using namespace ppc;

updateCmpntDecorator::updateCmpntDecorator(
	UpdateComponent& updatePtr): uCmpntHandle_(&updatePtr){}

updateCmpntDecorator::~updateCmpntDecorator() {
	delete uCmpntHandle_;
}

Entity* updateCmpntDecorator::getEntity() {
	return uCmpntHandle_->getEntity();
}

void updateCmpntDecorator::setEntity(Entity* e) {
	uCmpntHandle_->setEntity(e);
}

void updateCmpntDecorator::recieveMessage(msgType message) {
	uCmpntHandle_->recieveMessage(message);
}

void updateCmpntDecorator::update(sf::Time& deltaTime) {
	uCmpntHandle_->update(deltaTime);
}