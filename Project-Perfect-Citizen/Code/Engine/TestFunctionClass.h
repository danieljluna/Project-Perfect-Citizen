#pragma once
#include "FunctionObserver.h"
///WRITTEN BY ANDY BADEN
////////////////////////////////////////////////////
///@brief TestFunctionClass is just that...
///a class used to test the capabillities of the 
///function observers
////////////////////////////////////////////////////
class TestFunctionClass {
private:
	int x;
public:
	TestFunctionClass();
	bool callFunc(sf::Event&);
};