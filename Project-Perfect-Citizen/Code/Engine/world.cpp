//World.cpp
//Nader Sleem
#include "world.h"
#include "debug.h"


std::vector<ppc::World*> ppc::World::worldsVector;

ppc::World::World() {
	for (size_t i = 0; i < MAX_DESKTOP_COUNT; i++) {
		this->desktops_[i] = nullptr;
	}

	ppc::World::worldsVector.push_back(this);
	this->worldIndex = ppc::World::worldsVector.size() - 1;
}

ppc::World::~World() {
	for (size_t i = 0; i < MAX_DESKTOP_COUNT; i++) {
		if (this->desktops_[i] != nullptr) {
			//need to add more code here depending
			//on what desktops look like

			//Should I be deleting the contents of the array???
			// Todo: ask during meeting

			delete this->desktops_[i];
			this->desktops_[i] = nullptr;
		}
	}
	World::worldsVector.erase(World::worldsVector.begin() +
		this->worldIndex);
}

size_t ppc::World::desktopCount() const {
	return desktopCount_;
}

ppc::Desktop* ppc::World::getDesktop(int index) const{
	if ((size_t)index > desktopCount() || index < 0) return nullptr;
	return desktops_[index];
}

int ppc::World::getIndex(Desktop* d) {
	int result = -1;

	if (d == nullptr) return result;

	//Search through the Components_
	for (size_t i = 0; i < desktopCount_; ++i) {
		//If we find the cmpnt specified
		if (desktops_[i] == d) {
			//Overwrite the result
			result = i;
			break;
		}
	}

	return result;
}

int ppc::World::addDesktop(Desktop* d) {
	//Test if we have room for the cmpnt
	if (desktopCount_ < MAX_DESKTOP_COUNT) {
		//Store cmpnt and return the index it was stored at
		desktops_[desktopCount_] = d;
		//may need to add more here later based on
		// implementation of desktop
		//return its index and then increment size counter
		return desktopCount_++;
	} else {
		//If there is no room, return -1
		return -1;
	}
}

void ppc::World::removeDesktop(Desktop* d) {
	if (d == nullptr) return;
	removeDesktop(World::getIndex(d));
}

void ppc::World::removeDesktop(int index) {
	if ((size_t)index > desktopCount() || index < 0) return;
	//save index
	size_t i = index;

	//may need to add more here later based on
	// implementation of desktop

	// set what we want to remove to null
	desktops_[index] = nullptr;
	//while what is next to i is within our bounds
	while (i + 1 < desktopCount_) {
		//save what [i] is (should be nullptr)
		Desktop* temp = desktops_[i];
		//set [i] to [i+1]
		desktops_[i] = desktops_[i + 1];
		//set [i+1] to what [i] originally was
		desktops_[i + 1] = temp;
		// increment [i]
		i = i + 1;
	}
	//decrement amount of things we have in array
	--desktopCount_;
}