#include "NetworkInputCmpnt.h"

ppc::NetworkInputCmpnt::NetworkInputCmpnt(Network& n):
	InputComponent(3), network_(&n){}

ppc::NetworkInputCmpnt::~NetworkInputCmpnt() {
}

bool ppc::NetworkInputCmpnt::registerInput(sf::Event& ev) {
	return false;
}
