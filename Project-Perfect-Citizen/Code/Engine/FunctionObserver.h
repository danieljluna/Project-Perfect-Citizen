#pragma once
#include "observer.h"

template<class T>
class FunctionObserver : public ppc::BaseObserver {
public:

	bool(T::*functionPointer)(sf::Event&);

	FunctionObserver(bool(T::*myFunction)(sf::Event&)) {
		this->functionPointer = myFunction;
	}
	virtual bool eventHandler(sf::Event& ev) {
		std::cout << this->id << std::endl;
		//(T::functionPointer)(ev);
		//(*T.*(this->functionPointer))(testEvent);
		return true;
	}
};