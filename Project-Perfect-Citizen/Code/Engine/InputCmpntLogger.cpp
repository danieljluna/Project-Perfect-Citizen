#include "debug.h"
#include "InputCmpntLogger.h"
#include <iostream>

using namespace ppc;

inputCmpntLogger::inputCmpntLogger(InputComponent& inputPtr, 
	std::ostream& out): iCmpntHandle_(&inputPtr), out_(out){}

inputCmpntLogger:: ~inputCmpntLogger() {
	iCmpntHandle_ = nullptr;
}

Entity* inputCmpntLogger::getEntity() {
	out_ << "InputCmpntLogger: Getting Entity of Cmpnt: " <<
		iCmpntHandle_ << std::endl;
	
	return iCmpntHandle_->getEntity();
}

void inputCmpntLogger::setEntity(Entity* e) {
	out_ << "InputCmpntLogger: Setting Entity of Cmpnt: " <<
		iCmpntHandle_ << std::endl;
	iCmpntHandle_->setEntity(e);
}

void inputCmpntLogger::recieveMessage(msgType message) {
	out_ << "InputCmpntLogger: Recieving Msg in Cmpnt: " <<
		iCmpntHandle_ << std::endl;
	iCmpntHandle_->recieveMessage(message);
	out_ << "InputCmpntLogger: Recieved Msg: " <<
		message << std::endl;
}

bool inputCmpntLogger::registerInput(sf::Event& ev) {
	out_ << "InputCmpntLogger: Registering Event in Cmpnt: " <<
		iCmpntHandle_ << std::endl;
	return iCmpntHandle_->registerInput(ev);
	out_ << "InputCmpntLogger: Event " << ev.type << 
		" registered." << std::endl;
}