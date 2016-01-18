#include "updateComponent.h"

using namespace ppc;
/////////////////////////////////////////////////////
// Update Vector
//You need this line when you have a static vector 
////////////////////////////////////////////////////
std::vector<updateComponent*> updateComponent::updateVector;


/////////////////////////////
// CTOR
/////////////////////////////
updateComponent::updateComponent() {
	updateComponent::updateVector.push_back(this);
	this->index = updateComponent::updateVector.size() - 1;
}

/////////////////////////////
// DTOR
/////////////////////////////
updateComponent::~updateComponent() {
	removeElement(this->index);
}

//////////////////////////////
// Update Vector Management
/////////////////////////////
void updateComponent::removeElement(int index) {
	updateComponent::updateVector.erase(updateComponent::updateVector.begin() + index);
}