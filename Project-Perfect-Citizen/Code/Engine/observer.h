#pragma once
#include "event.h"
#include <SFML/Graphics.hpp>


namespace ppc {


///////////////////////////////////////////////////////////////////////
///@brief Abstract base class for all observer systems.
///@details If you want to create a class that observes something, make
/// it a child of this. An example could be an achievment listener.
///////////////////////////////////////////////////////////////////////
class BaseObserver {
	//allows subjects to manage their observers
	friend class Subject;

private:
	BaseObserver* next;
	BaseObserver* prev;

    static unsigned int id_counter_;

    bool inUse;

public:

    /// @brief Default Constructor
    BaseObserver();

    /// @brief Virtual Destructor
    ~BaseObserver();

	///////////////////////////////////////////////////////////////////
	///@brief Virtaul eventHandler
    ///@details This is the function that will be called when an 
    /// Observer is notified of an event of interest.
	///@param event The event this Observer was notified of.
    ///@return Denotes whether this observer propogates the event.
    ///////////////////////////////////////////////////////////////////
	virtual bool eventHandler(sf::Event& ev) = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Returns if this Observer is in use by a Subject
    ///////////////////////////////////////////////////////////////////
    bool isInUse();

    ///////////////////////////////////////////////////////////////////
	/// @brief Used to ID Observers for debugging
    ///////////////////////////////////////////////////////////////////
	const unsigned int id;


};



};
