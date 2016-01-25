#include "renderComponent.h"
//You need this when you have a static vector that contains a class data type
std::vector<ppc::RenderComponent*> ppc::RenderComponent::renderVector;


void ppc::RenderComponent::removeElement(int index)
{
	ppc::RenderComponent::renderVector.erase(ppc::RenderComponent::renderVector.begin() + index);
}
