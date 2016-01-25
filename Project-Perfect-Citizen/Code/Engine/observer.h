#pragma once
#include "event.h"
///////////////////////////////////////////////
///@brief Abstract base class for all observer
///systems.
///@details IF you want to create a class that
///observes something, make it a child of this.
///An example could be an achievment listener.
///You can instantiate an object of type 
///observer, but you probably shouldnt without
///asking the programming team.
///////////////////////////////////////////////
using namespace std;
class Observer {
	//allows subjects to manage their observers
	friend class Subject;
private:
	Observer* next;
	Observer* prev;
public:
	//virutal ~Observer() {};
	Observer() : next(nullptr), prev(nullptr) {};
	///////////////////////////////////////////////
	///@brief virtaul eventHandler. This has base
	///functionality, but chances are you're going
	///to redefine it in its child classes.
	///@param event is the event that is being
	///passed by the subject to all of its 
	///currently linked observers. 
	///////////////////////////////////////////////
	virtual void eventHandler(ppc::Event event);
	//this is a UID to help you get a sense of what
	//although you could use anything else you'd
	//prefer...
	int numberIdentifier;

};