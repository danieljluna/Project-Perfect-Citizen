//Programmed by Andy
#pragma once
#include "observer.h"
///////////////////////////////////////////////
///@brief This is the subject base class. It is
///the parent of all objects that wish to have
///observers.
///@details Even though you can, dont
///instantiate an object of type Subject
///(subject to change, but for now, dont 
///without asking us about it.
//////////////////////////////////////////////
class Subject {
private:
	int numberOfObservers;
	//The front of the doubly linked list of observers
	//that every child of subject may have. 
	Observer* observerHead;
public:
	Subject() : observerHead(nullptr) {};
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	Observer* getObserverHead();
	void printObservers();
protected:
	void sendEvent(ppc::Event event);
	
};