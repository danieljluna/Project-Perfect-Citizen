#pragma once
#include "observer.h"
#include "event.h"
//WRITTEN BY ANDY BADEN

namespace ppc {

////////////////////////////////////////////////////////////////////
///@brief FreeFunctionObserver is a templated observer child dedicated to
///calling non-member functions or "free functions". 
///@details This Class is useful because it allows the user to 
///plug in functions and an object used to call that function. 
///Dont forget to define what T is when instantiating this class!
////////////////////////////////////////////////////////////////////
template <class T>
class FreeFunctionObserver : public BaseObserver {
private:
	////////////////////////////////////////////////////////////////////
	///@brief Pointer of an object type. This is used to call functions
	///inside Event handler as it is necessary to have an object to call
	///the functions from. 
	////////////////////////////////////////////////////////////////////
	T* target;
	////////////////////////////////////////////////////////////////////
	///@brief function pointer to a function that accepts a class pointer T
	/// and an Event
	////////////////////////////////////////////////////////////////////
	bool(*functionPointer)(T*, Event);
public:
	////////////////////////////////////////////////////////////////////
	///@brief constructor for FreeFunctionObserver. Passes in the address
	///of a function of the proper  type, along with a pointer to an object
	///type used to call the relevent functions inside the freeFunction.
	///make sure you use define the template perameters when defining
	///the function. 
	///@param myFunction: function pointer of type void(*)(T*, Event)
	///@param comfyTarget: object to be embedded in the class. Used to call
	///myfunction inside FreeFunctionObserver::EventHandler
	////////////////////////////////////////////////////////////////////
	FreeFunctionObserver(bool(*myFunction)(T*, Event ev), T* comfyTarget) {
		this->functionPointer = myFunction;
		this->target = comfyTarget;
	}
	////////////////////////////////////////////////////////////////////
	///@brief Pure virtual function that was inheirited from 
	///ppc::baseObserver. Calls the embedded function in the class. 
	///@param event recieved. 
	////////////////////////////////////////////////////////////////////
    bool eventHandler(Event ev) override {
		functionPointer(target, ev);
		return true;
	}
};


};
