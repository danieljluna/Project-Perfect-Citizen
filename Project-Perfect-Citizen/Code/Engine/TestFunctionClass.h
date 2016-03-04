#pragma once
#include "FunctionObserver.h"

//using testFunc = bool(*)(sf::Event&);
class TestFunctionClass {
private:
	int x;
public:
	TestFunctionClass();
	bool callFunc(sf::Event&);
};