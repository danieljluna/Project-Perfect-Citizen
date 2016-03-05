#pragma once
#include "observer.h"

template<class T>
class FunctionObserver : public ppc::BaseObserver {
private:
	T* target;
public:
	bool(T::*functionPointer)(sf::Event&);

	FunctionObserver(bool(T::*myFunction)(sf::Event&), T* comfyTarget) {
		this->functionPointer = myFunction;
		this->target = comfyTarget;
	}
	virtual bool eventHandler(sf::Event& ev) {
		std::cout << this->id << std::endl;
		(*target.*(this->functionPointer))(ev);
		return true;
	}
};