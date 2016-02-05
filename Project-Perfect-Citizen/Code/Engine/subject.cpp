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




void Subject::removeObserver(unsigned int obsvr_id, 
                             unsigned int range) {

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


///////////////////////////////////////////////////////////////////////
// Private Helpers
///////////////////////////////////////////////////////////////////////

//Helper to check if an Observer is in the Subject. Returns nullptr if
//not found.
BaseObserver* Subject::find(BaseObserver* observer) {
    BaseObserver* result = nullptr;

    for (BaseObserver* i = observerHead; i != nullptr; i = i->next) {
        if (i == observer) {
            result = observer;
            break;
        }
    }

    return result;
}




//Helper to check if an Observer is in the Subject. Returns nullptr if
//not found. Here, it checks using the id (possibly a range of ids)
BaseObserver* Subject::find(unsigned int ObsvrId, unsigned int range) {
    BaseObserver* result = nullptr;

    for (BaseObserver* i = observerHead; i != nullptr; i = i->next) {
        if ((i->id >= ObsvrId) && (i->id < ObsvrId + range)) {
            result = i;
            break;
        }
    }

    return result;
}




//Removes the Observer. Precondition that observer is actually in this
//      Subject's linked list.
void Subject::rmObserver(BaseObserver* obsvr) {
    //If there is an observer before this one:
    if (obsvr->prev != nullptr) {
        //Set that observer's next to this observer's next
        obsvr->prev->next = obsvr->next;
    } else {
        //We need to update the head to point to the next observer
        observerHead = obsvr->next;
    }

    //If there is an observer after this one:
    if (obsvr->next != nullptr) {
        //Set that observer's prev to this observer's prev
        obsvr->next->prev = obsvr->prev;
    }
}

