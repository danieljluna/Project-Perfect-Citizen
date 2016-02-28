#include "NetworkRenderCmpnt.h"

using namespace ppc;

NetworkRenderComponent::NetworkRenderComponent(ppc::Network& n): 
	network_(&n) {}

NetworkRenderComponent::~NetworkRenderComponent() {
}

void NetworkRenderComponent::draw(sf::RenderTarget & target, 
	sf::RenderStates states) const {

	target.draw(*network_, states);
}

void NetworkRenderComponent::recieveMessage(msgType code) {
}


