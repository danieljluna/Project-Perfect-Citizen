#include "updateComponent.h"

using namespace ppc;
//You need this line when you have a static vector 
std::vector<updateComponent*> updateComponent::updateVector;

void updateComponent::removeElement(int index) {
	updateComponent::updateVector.erase(updateComponent::updateVector.begin() + index);
}