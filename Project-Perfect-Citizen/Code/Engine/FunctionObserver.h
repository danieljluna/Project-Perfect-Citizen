#pragma once
#include "observer.h"

class FunctionObserver : public ppc::BaseObserver {
private:
	bool(*obsFunc)(sf::Event&);
public:
	FunctionObserver(bool (*myFunction)(sf::Event&));
	virtual bool eventHandler(sf::Event& ev);
};