#include "NetworkInputCmpnt.h"
#include "../Engine/debug.h"

ppc::NetworkInputCmpnt::NetworkInputCmpnt(Network& n, 
	ppc::InputHandler& ih) : InputComponent(), network_(&n), handle_(ih){

	//Make every vertex draggable
	//for (size_t i = 0; i < network_->size(); i++) {
		DraggableInput* dI = new DraggableInput(network_->vert(0));
		network_->vert(0).applyDraggable(*dI, handle_);
		dI->setBounds(network_->vert(0).getLocalBounds());
		DEBUGF("ni", network_->vert(0).getLocalBounds().left);
		DEBUGF("ni", network_->vert(0).getLocalBounds().top);
		DEBUGF("ni", network_->vert(0).getLocalBounds().width);
		DEBUGF("ni", network_->vert(0).getLocalBounds().height);
		drags_.push_back(dI);
	//}

}

ppc::NetworkInputCmpnt::~NetworkInputCmpnt() {
	for (auto it = drags_.begin(); it != drags_.end(); ++it) {
		delete *it;
	}
}

bool ppc::NetworkInputCmpnt::registerInput(sf::Event& ev) {
	return false;
}
