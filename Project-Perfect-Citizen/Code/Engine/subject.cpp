#include "subject.h"
#include <iostream>
using namespace ppc;

//adds to the front. 
//TODO
void Subject::addObserver(BaseObserver* observer) {
		observer->next = observerHead;
		if (observerHead != nullptr) {
			observerHead->prev = observer;
		}
		observerHead = observer;
		observer->prev = nullptr;
	
}

void Subject::removeObserver(BaseObserver * observer){
	//if its the head
	
	if (observerHead == observer) {
		//there is only one 
		if (observerHead->next == nullptr) {
			BaseObserver* tempObserver = observerHead;
			observerHead = nullptr;
			tempObserver->prev = nullptr;
			tempObserver->next = nullptr;
			//delete observerHead;
			delete tempObserver;
			return;

		}
		else {
			BaseObserver* tempObserver = observerHead;
			observerHead = observerHead->next;
			observerHead->prev = nullptr;
			tempObserver->next = nullptr;
			tempObserver->prev = nullptr;
			delete tempObserver;
			return;
		}
	}

    BaseObserver* currentObserver = observerHead;
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

BaseObserver * Subject::getObserverHead()
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
    BaseObserver* currentObserver = this->observerHead;
	while (currentObserver != nullptr) {
		std::cout << "identifier is "<< currentObserver->id << std::endl;
		currentObserver = currentObserver->next;
	}
}

void Subject::sendEvent(sf::Event& event)
{
    BaseObserver* currentObserver = this->observerHead;
	if (observerHead == nullptr) {
		std::cout << "no observers connected to this object!" << std::endl;
		return;
	}

	while (currentObserver != nullptr) {
		currentObserver->eventHandler(event);
		currentObserver = currentObserver->next;
	}
}
