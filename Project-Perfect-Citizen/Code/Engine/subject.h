#pragma once
#include "observer.h"
//this class will eventually be abstract
class Subject {
private:
	int numberOfObservers;
	Observer* observerHead;
public:
	Subject() : observerHead(nullptr) {};
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	Observer* getObserverHead();
protected:
	void sendEvent(ppc::Event event);
	
};