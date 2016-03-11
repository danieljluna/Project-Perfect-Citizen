#include "debug.h"
#include "updateCmpntLogger.h"

using namespace ppc;


updateCmpntLogger::updateCmpntLogger(UpdateComponent& updatePtr,
	std::ostream& out): updateCmpntDecorator(updatePtr), out_(out) {}

updateCmpntLogger::~updateCmpntLogger() {}

Entity* updateCmpntLogger::getEntity() {
	out_ << "UpdateCmpntLogger: Getting Entity of Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	return this->getDecoTarget()->getEntity();
}

void updateCmpntLogger::setEntity(Entity* e) {
	out_ << "UpdateCmpntLogger: Setting Entity of Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->setEntity(e);
}

void updateCmpntLogger::recieveMessage(msgType message) {
	out_ << "UpdateCmpntLogger: Recieving Msg in Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->recieveMessage(message);
	out_ << "UpdateCmpntLogger: Recieved Msg: " << 
		message << std::endl;
}

void updateCmpntLogger::update(sf::Time& deltaTime) {
	out_ << "UpdateCmpntLogger: Calling update in Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->update(deltaTime);
}