#include "subject.h"
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
			observer->next = nullptr;
			observer->prev = nullptr;
			delete observer;
			return;
		}
		else {
			Observer* tempObserver = observerHead;
			observerHead->next->prev = nullptr;
			observerHead->next = nullptr;
			observerHead = observerHead->next;
			delete tempObserver;
			return;
		}
	}

	Observer* currentObserver = observerHead;
	while (currentObserver != nullptr) {
		if (currentObserver->next = observer) {
			currentObserver->next = observer->next;
			observer->next->prev = currentObserver;
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
