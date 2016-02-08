#include "EntityDecorator.h"

using namespace ppc;

EntityDecorator::EntityDecorator(Entity& entityPtr):entityHandle_(&entityPtr) {}

EntityDecorator:: ~EntityDecorator() {
	delete entityHandle_;
}

size_t EntityDecorator::cmpntCount() {
	return entityHandle_->cmpntCount();
}

Component* EntityDecorator::getComponent(size_t index) {
	return entityHandle_->getComponent(index);
}

int EntityDecorator::getIndex(Component* cmpnt) {
	return entityHandle_->getIndex(cmpnt);
}

int EntityDecorator::addComponent(Component* cmpnt) {
	return entityHandle_->addComponent(cmpnt);
}

void EntityDecorator::removeComponent(Component* cmpnt) {
	entityHandle_->removeComponent(cmpnt);
}

void EntityDecorator::removeComponent(size_t index) {
	entityHandle_->removeComponent(index);
}

void EntityDecorator::broadcastMessage(msgType message) {
	entityHandle_->broadcastMessage(message);
}