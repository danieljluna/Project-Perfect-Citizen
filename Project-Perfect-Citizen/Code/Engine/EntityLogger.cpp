#include "debug.h"
#include "EntityLogger.h"
#include <iostream>

using namespace ppc;


EntityLogger::EntityLogger(Entity& entityPtr, std::ostream& out):
	EntityDecorator(entityPtr), out_(out) {}

EntityLogger::~EntityLogger() {}


size_t EntityLogger::cmpntCount() {
	size_t count = this->getDecoTarget()->cmpntCount();

	out_ << "Entity Logger: Counting Cmpnts of Entity: " << 
		this->getDecoTarget() << ": " << count << 
		" cmpnts" << std::endl;

	return count;
}

Component* EntityLogger::getComponent(size_t index) {
	out_ << "Entity Logger: Getting Cmpnt of Entity: " << 
		this->getDecoTarget() << " at index: " << index << std::endl;

	return this->getDecoTarget()->getComponent(index);
}

int EntityLogger::getIndex(Component* cmpnt) {
	int i = this->getDecoTarget()->getIndex(cmpnt);

	out_ << "Entity Logger: Getting Index of Cmpnt in Entity: " << 
		this->getDecoTarget() << ": Index of " << cmpnt << 
		" found at " << i << std::endl;

	return i;
}

int EntityLogger::addComponent(Component* cmpnt) {
	int i = this->getDecoTarget()->addComponent(cmpnt);
	out_ << "Entity Logger: Adding cmpnt in Entity: " << 
		this->getDecoTarget() << ": Cmpnt added to index: " <<
		i << std::endl;

	return i;
}

void EntityLogger::removeComponent(Component* cmpnt) {
	out_ << "Entity Logger: Removing Cmpnt in Entity: " << 
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->removeComponent(cmpnt);
}

void EntityLogger::removeComponent(size_t index) {
	out_ << "Entity Logger: Removing Cmpnt in Entity: " << 
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->removeComponent(index);
}

void EntityLogger::broadcastMessage(msgType message) {
	out_ << "Entity Logger: Broadcasting Msg in Entity: " <<
		this->getDecoTarget() << " : Broadcasting " << 
		message << std::endl;

	this->getDecoTarget()->broadcastMessage(message);

}