//Programmed by Andy
#pragma once
#include "observer.h"
#include <iostream>

///////////////////////////////////////////////
///@brief Test child class for Observer
///////////////////////////////////////////////
class TestObserver : public Observer {
public:
	////////////////////////////////////////////////
	///@brief This function is inherited from
	///Observer. 
	///@details Its not necessary for the child 
	///to redifine eventHandler, but you're probably
	///going to have to in most situations.
	///@param Event to be parsed. 
	///////////////////////////////////////////////
	virtual void eventHandler(ppc::Event event);
};
