#include "updateComponent.h"

using namespace ppc;

void updateComponent::removeElement(int index) {
	updateComponent::updateVector.erase(updateComponent::updateVector.begin() + index);
}