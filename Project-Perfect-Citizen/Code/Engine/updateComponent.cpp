//UpdateComponent.cpp
// Nader Sleem

#include "updateComponent.h"

using namespace ppc;
/////////////////////////////////////////////////////
// Update Vector
//You need this line when you have a static vector 
////////////////////////////////////////////////////
std::vector<UpdateComponent*> UpdateComponent::updateVector;


/////////////////////////////
// CTOR
/////////////////////////////
UpdateComponent::UpdateComponent() {
	UpdateComponent::updateVector.push_back(this);
	this->index = UpdateComponent::updateVector.size() - 1;
}

/////////////////////////////
// DTOR
/////////////////////////////
UpdateComponent::~UpdateComponent() {
	removeElement(this->index);
}

//////////////////////////////
// Update Vector Management
/////////////////////////////
void UpdateComponent::removeElement(int index) {
	UpdateComponent::updateVector.erase(UpdateComponent::updateVector.begin() + index);
}