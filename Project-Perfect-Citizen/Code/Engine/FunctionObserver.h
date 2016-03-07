#pragma once
#include "observer.h"
//WRITTEN BY ANDY BADEN
////////////////////////////////////////////////////////////////////
///@brief FreeFunctionObserver is a templated observer child dedicated to
///calling member functions 
///@details This Class is useful because it allows the user to 
///plug in functions and an object used to call that function. 
///Dont forget to define what T is when instantiating this class!
////////////////////////////////////////////////////////////////////

//THIS CLASS IS BASICALLY THE SAME AS FreeFunctionObserver
//LOOK THERE FOR MORE INFO ON INDIVIDUAL FUNCTIONS
template<class T>
class MemberFunctionObserver : public ppc::BaseObserver {
private:
	T* target;
public:
	bool(T::*functionPointer)(sf::Event&);

	MemberFunctionObserver(bool(T::*myFunction)(sf::Event&), T* comfyTarget) {
		this->functionPointer = myFunction;
		this->target = comfyTarget;
	}
	virtual bool eventHandler(sf::Event& ev) {
		std::count << this->id << std::endl;
		(*target.*(this->functionPointer))(ev);
		return true;
	}
};