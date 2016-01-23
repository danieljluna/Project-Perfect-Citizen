#pragma once
#include "event.h"
//this class will eventually be abstract
using namespace std;
class Observer {
	friend class Subject;
private:
	Observer* next;
	Observer* prev;
public:
	//virtual ~Observer() {};
	Observer() : next(nullptr), prev(nullptr) {};
	//this is for my own sanity. Itll give me something to refer to.
	//this is to be virtual (eventually)
	void eventHandler(ppc::Event event);
	int numberIdentifier;

};