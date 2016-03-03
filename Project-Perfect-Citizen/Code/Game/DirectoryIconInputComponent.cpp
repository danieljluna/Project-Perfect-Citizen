#include "DirectoryIconInputComponent.h"

ppc::DirectoryIconInputComponent::DirectoryIconInputComponent(sf::Image & buttonSheet_) : bs_(buttonSheet_)
{
	
}

ppc::DirectoryIconInputComponent::~DirectoryIconInputComponent()
{
}

bool ppc::DirectoryIconInputComponent::registerInput(sf::Event & ev)
{
	return false;
}

void ppc::DirectoryIconInputComponent::recieveMessage(msgType message)
{
	return;
}
