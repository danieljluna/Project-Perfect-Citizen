#include "subject.h"
#include <iostream>
//adds to the front. 
//TODO
void Subject::addObserver(Observer* observer) {
		observer->next = observerHead;
		if (observerHead != nullptr) {
			observerHead->prev = observer;
		}
		observerHead = observer;
		observer->prev = nullptr;
	
}

void Subject::removeObserver(Observer * observer){
	//if its the head
	
	if (observerHead == observer) {
		//there is only one 
		if (observerHead->next == nullptr) {
			Observer* tempObserver = observerHead;
			observerHead = nullptr;
			tempObserver->prev = nullptr;
			tempObserver->next = nullptr;
			//delete observerHead;
			delete tempObserver;
			return;

		}
		else {
			Observer* tempObserver = observerHead;
			observerHead = observerHead->next;
			observerHead->prev = nullptr;
			tempObserver->next = nullptr;
			tempObserver->prev = nullptr;
			delete tempObserver;
			return;
		}
	}

	Observer* currentObserver = observerHead;
	while (currentObserver != nullptr) {
		if (currentObserver->next == observer) {
			currentObserver->next = observer->next;
			if (observer->next != nullptr) {
				observer->next->prev = currentObserver;
			}
			observer->next = nullptr;
			observer->prev = nullptr;
			delete observer;
			return;
		}
		currentObserver = currentObserver->next;
	}
}

Observer * Subject::getObserverHead()
{
	if (this->observerHead == nullptr) {
		
		return nullptr;
	}
	else {
		return this->observerHead;
	}
}

void Subject::printObservers()
{
	Observer* currentObserver = this->observerHead;
	while (currentObserver != nullptr) {
		std::cout << "identifier is "<< currentObserver->numberIdentifier << endl;
		currentObserver = currentObserver->next;
	}
}

void Subject::sendEvent(ppc::Event event)
{
	Observer* currentObserver = this->observerHead;
	if (observerHead == nullptr) {
		cout << "no observers connected to this object!" << endl;
		return;
	}

	while (currentObserver != nullptr) {
		currentObserver->eventHandler(event);
		currentObserver = currentObserver->next;
	}
}
