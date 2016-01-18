#include "renderComponent.h"
//You need this when you have a static vector that contains a class data type
std::vector<RenderComponent*> RenderComponent::renderVector;


void RenderComponent::removeElement(int index)
{
	RenderComponent::renderVector.erase(RenderComponent::renderVector.begin() + index);
}
