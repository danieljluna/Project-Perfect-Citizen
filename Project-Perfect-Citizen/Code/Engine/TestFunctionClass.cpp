#include "TestFunctionClass.h"
#include <iostream>
#include <string>

TestFunctionClass::TestFunctionClass()
{
}

bool TestFunctionClass::callFunc(sf::Event&)
{
	std::cout << "Inside callFun! It worked!" << std::endl;
	return true;
}
