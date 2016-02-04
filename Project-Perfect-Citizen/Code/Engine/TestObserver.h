//Programmed by Andy
#pragma once
#include "observer.h"
#include <iostream>


namespace ppc {


///////////////////////////////////////////////
///@brief Test child class for Observer
///////////////////////////////////////////////
class TestObserver : public BaseObserver {
public:
	////////////////////////////////////////////////
	///@brief This function is inherited from
	///Observer. 
	///@details Its not necessary for the child 
	///to redifine eventHandler, but you're probably
	///going to have to in most situations.
	///@param Event to be parsed. 
	///////////////////////////////////////////////
	virtual void eventHandler(sf::Event event);
};


};