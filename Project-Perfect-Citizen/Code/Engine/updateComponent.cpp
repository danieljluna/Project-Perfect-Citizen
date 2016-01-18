#include "updateComponent.h"

using namespace ppc;

std::vector<updateComponent*> updateComponent::updateVector;

void updateComponent::removeElement(int index) {
	updateComponent::updateVector.erase(updateComponent::updateVector.begin() + index);
}