//Programmed by Andy
#pragma once
#include "observer.h"
#include <SFML/Graphics.hpp>

namespace ppc {

///////////////////////////////////////////////
///@brief This is the subject  class. Stick a
///as a member variable inside any class you 
///want observed 
///@details Observers is a friend class of 
///subject and therefore, any adding or removing
///of observers is done by the object and not
///by the observers. 
//////////////////////////////////////////////
class Subject {
public:
	Subject() : observerHead(nullptr) {};
	void addObserver(BaseObserver* observer);
	void removeObserver(BaseObserver* observer);
    void removeObserver(unsigned int obsvr_id, unsigned int range = 1);
	BaseObserver* getObserverHead();
	void printObservers();

	void sendEvent(sf::Event& event);


private:
    //See .cpp
    BaseObserver* find(BaseObserver* observer);
    //See .cpp
    BaseObserver* find(unsigned int ObsvrId, unsigned int range = 1);
    //See .cpp
    void rmObserver(BaseObserver* observer);

    //The front of the doubly linked list of observers
    //that every child of subject may have. 
    BaseObserver* observerHead;
};


};
