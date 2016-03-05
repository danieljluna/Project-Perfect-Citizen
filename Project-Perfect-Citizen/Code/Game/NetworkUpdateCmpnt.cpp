#include "NetworkUpdateCmpnt.h"
#include "../Engine/debug.h"

ppc::NetworkUpdateCmpnt::NetworkUpdateCmpnt(Network& n): network_(&n),
	drags_(nullptr) {}

ppc::NetworkUpdateCmpnt::NetworkUpdateCmpnt(Network& n,
	sf::FloatRect b) : network_(&n), bounds_(b), 
	drags_(nullptr) {}

void ppc::NetworkUpdateCmpnt::setBounds(sf::FloatRect b){
	bounds_ = b;
}

void ppc::NetworkUpdateCmpnt::setDrags(vector<ppc::DraggableInput*>* ds) {
	drags_ = ds;
}

void ppc::NetworkUpdateCmpnt::update(sf::Time & deltaTime) {
	if (drags_ == nullptr) return;
	for (size_t i = 0; i < network_->size(); i++) {
		sf::FloatRect vertBound = network_->vert(i).getLocalBounds();
		float right = bounds_.left + bounds_.width;
		float bottom = bounds_.top + bounds_.height;
		if (vertBound.left < bounds_.left) {
			network_->vert(i).setPosition(bounds_.left,vertBound.top);
		} else if (vertBound.left + vertBound.width > right) {
			network_->vert(i).setPosition(right - vertBound.width, vertBound.top);
		} else if (vertBound.top < bounds_.top) {
			network_->vert(i).setPosition(vertBound.left, bounds_.top);
		} else if (vertBound.top + vertBound.height > bottom) {
			network_->vert(i).setPosition(vertBound.left, bottom - vertBound.height);
		}
		drags_->at(i)->setBounds(network_->vert(i).getLocalBounds());
	}
}




