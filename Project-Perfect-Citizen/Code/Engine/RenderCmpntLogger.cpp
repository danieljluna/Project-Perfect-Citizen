#include "RenderCmpntLogger.h"

using namespace ppc;

renderCmpntLogger::renderCmpntLogger(RenderComponent& updatePtr,
	std::ostream& out): renderCmpntDecorator(updatePtr), out_(out){ }

renderCmpntLogger::~renderCmpntLogger() {}

Entity* renderCmpntLogger::getEntity() {
	out_ << "RenderCmpntLogger: Getting Entity of Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	return this->getDecoTarget()->getEntity();
}

void renderCmpntLogger::setEntity(Entity* e) {
	out_ << "RenderCmpntLogger: Setting Entity of Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->setEntity(e);
}

void renderCmpntLogger::recieveMessage(msgType message) {
	out_ << "RenderCmpntLogger: Recieving Msg in Cmpnt: " <<
		this->getDecoTarget() << std::endl;
	this->getDecoTarget()->recieveMessage(message);
	out_ << "RenderCmpntLogger: Recieved Msg: " <<
		message << std::endl;
}

void renderCmpntLogger::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	out_ << "RenderCmpntLogger: Calling draw in Cmpnt: " <<
		this->getDecoTarget() << std::endl;

	target.draw(*(this->getDecoTarget()), states);
}