#include "FunctionObserver.h"
#include "../Engine/debug.h"
FunctionObserver::FunctionObserver(bool(*myFunction)(sf::Event &))
{
	this->obsFunc = myFunction;
}

bool FunctionObserver::eventHandler(sf::Event & ev)
{
	return obsFunc(ev);
}
