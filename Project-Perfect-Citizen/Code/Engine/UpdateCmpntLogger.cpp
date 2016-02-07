#include "updateCmpntLogger.h"

using namespace ppc;
using namespace std;

updateCmpntLogger::updateCmpntLogger(UpdateComponent& updatePtr,
	std::ostream& out): updateCmpntDecorator(updatePtr), out_(out) {}

updateCmpntLogger::~updateCmpntLogger() {}

Entity* updateCmpntLogger::getEntity() {
	out_ << "UpdateCmpntLogger: Getting Entity of Cmpnt: " <<
		this->getDecoTarget() << endl;
	return this->getDecoTarget()->getEntity();
}

void updateCmpntLogger::recieveMessage(msgType message) {
	out_ << "UpdateCmpntLogger: Recieving Msg in Cmpnt: " <<
		this->getDecoTarget();
	this->getDecoTarget()->recieveMessage(message);
	out_ << "UpdateCmpntLogger: Recieved Msg: " << message << endl;
}

void updateCmpntLogger::update(sf::Time& deltaTime) {
	out_ << "UpdateCmpntLogger: Calling update in Cmpnt: " <<
		this->getDecoTarget();
	this->getDecoTarget()->update(deltaTime);
}