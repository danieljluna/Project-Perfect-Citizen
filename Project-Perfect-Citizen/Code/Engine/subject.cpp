
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
        observer->watching_ = this;
}

void ppc::Subject::addObserverToBack(BaseObserver * observer)
{
	//if list is empty, call addObsever (it handles that already)
	if (observerHead == nullptr) {
		this->addObserver(observer);
		return;
	}

	BaseObserver* current = this->observerHead;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = observer;
	observer->prev = current;
}

void Subject::removeObserver(BaseObserver * observer){
    //If the observer is attatched to the subject:
    if (find(observer) != nullptr) {
        rmObserver(observer);
    }
}




void Subject::removeObserver(unsigned int obsvr_id, 
                             unsigned int range) {
    BaseObserver* temp = find(obsvr_id, range);
    while (temp != nullptr) {
        rmObserver(temp);
        temp = find(obsvr_id, range);
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
        if (!currentObserver->eventHandler(event)) {
            //Observer returned false, denoting it wants to stop event 
            //  propagation
            currentObserver = nullptr;
        } else {
            currentObserver = currentObserver->next;
        }
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

    obsvr->watching_ = nullptr;
}

