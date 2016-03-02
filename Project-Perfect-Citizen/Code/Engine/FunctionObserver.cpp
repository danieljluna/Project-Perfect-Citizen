#include "debug.h"
#include "FunctionObserver.h"
#include <iostream>
#include <string>
FunctionObserver::FunctionObserver(bool(*myFunction)(sf::Event &))
{
	this->obsFunc = myFunction;
}

bool FunctionObserver::eventHandler(sf::Event & ev)
{
	std::cout << this->id << std::endl;
	return obsFunc(ev);
}
