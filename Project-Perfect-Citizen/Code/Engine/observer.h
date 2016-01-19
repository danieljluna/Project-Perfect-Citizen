#pragma once
#include "event.h"
class Observer {
	friend class Subject;
private:
	Observer* next;
	Observer* prev;
public:
	virtual ~Observer() {};
	virtual void catchEvent() = 0;
	Observer() : next(nullptr), prev(nullptr) {};
	//this is for my own sanity. Itll give me something to refer to.
	void exampleEventHandler(Event event);

};