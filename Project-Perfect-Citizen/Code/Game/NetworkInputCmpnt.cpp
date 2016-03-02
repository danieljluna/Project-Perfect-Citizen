#include "NetworkInputCmpnt.h"

ppc::NetworkInputCmpnt::NetworkInputCmpnt(Network& n):
	InputComponent(3), network_(&n){}

ppc::NetworkInputCmpnt::~NetworkInputCmpnt() {
	if (network_ != nullptr) {
		delete network_;
		network_ = nullptr;
	}
}

bool ppc::NetworkInputCmpnt::registerInput(sf::Event& ev) {
	return false;
}
