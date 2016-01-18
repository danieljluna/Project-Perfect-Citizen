#include "renderComponent.h"

std::vector<RenderComponent*> RenderComponent::renderVector;

void RenderComponent::removeElement(int index)
{
	RenderComponent::renderVector.erase(RenderComponent::renderVector.begin() + index);
}
