#pragma once
#include "observer.h"
class Subject {
private:
	int numberOfObservers;
	Observer* observerHead;
public:
	Subject() : observerHead(nullptr) {};
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
protected:
	void sendEvent(Event event);
};