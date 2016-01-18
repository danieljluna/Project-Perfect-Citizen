#include "renderComponent.h"

void RenderComponent::removeElement(int index)
{
	RenderComponent::renderVector.erase(RenderComponent::renderVector.begin() + index);
}
